#include <cfloat>
#include <thread>
#include "render/PathTracer.h"
#include "util/Random.h"
#include "material/Material.h"

Random PathTracer::randX;

Random PathTracer::randY;

PathTracer::PathTracer(int spp, int maxDepth, int nThreads) {
    this->spp = spp;
    this->maxDepth = maxDepth;
    this->nThreads = nThreads;
}

void PathTracer::render(Camera * camera, Scene * scene, ImageBuffer * im) {
    int width = im->getWidth();
    int height = im->getHeight();

    ImageBuffer ** bufs = nullptr;
    std::thread ** workers = nullptr;

    // if multithreading
    if (nThreads > 1) {
        bufs = new ImageBuffer * [nThreads - 1];
        workers = new std::thread * [nThreads - 1];
        for (int i = 0; i < nThreads - 1; ++i) {
            bufs[i] = new ImageBuffer(width, height);
            workers[i] = new std::thread(
                    PathTracer::render0, camera, scene, bufs[i], spp / nThreads, maxDepth);
        }
    }

    // run the rest work in current thread
    int rest = spp - spp / nThreads * (nThreads - 1);
    render0(camera, scene, im, rest, maxDepth);

    if (nThreads > 1 && workers != nullptr) {
        // wait for other threads
        for (int i = 0; i < nThreads - 1; ++i) {
            workers[i]->join();
            delete workers[i];
        }
        delete [] workers;

        // reduce the results
        for (int k = 0; k < nThreads - 1; ++k) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    (*im)[i][j] += (*bufs[k])[i][j];
                }
            }
            delete bufs[k];
        }
        delete [] bufs;
    }

    // average
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            (*im)[i][j] /= (float) spp;
        }
    }
}

// in-thread rendering
void PathTracer::render0(Camera * camera, Scene * scene, ImageBuffer * im, int spp, int maxDepth) {
    int width = im->getWidth();
    int height = im->getHeight();
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= width; ++j) {
            Vector3f color(0, 0, 0);
            for (int k = 0; k < spp; ++k) {
                float dx = randX.randFloat(-0.5, 0.5);
                float x = ((float) j + dx) / (float) (width + 1);
                // note that the y-axis is from bottom to top
                float dy = randY.randFloat(-0.5, 0.5);
                float y = 1.f - ((float) i + dy) / (float) (height + 1);
                color += trace0(camera->getRay(x, y), scene, maxDepth);
            }
            (*im)[i - 1][j - 1] = color;
        }
    }
}

Vector3f PathTracer::trace0(const Ray & ray, Scene * scene, int maxDepth) {
    HitResult hitResult;
    if (scene->hitObject(ray, 1e-3, FLT_MAX, &hitResult)) {
        // 计算击中点的颜色
        return shade0(-ray.getDirection(), scene, maxDepth, 1, hitResult);
    }
    // 逸出场景
    return {0, 0, 0};
}

Vector3f PathTracer::shade0(const Vector3f & wo, Scene * scene, int maxDepth, int depth, const HitResult & hitResult) {
    Material * material = hitResult.facet->getMaterial();
    // 如果击中光源（发光材质），只有一个 L_e 项
    if (material->isEmitting()) {
        return material->getEmitting(wo, hitResult);
    }
    // 否则击中一个普通物体，先采样光源
    Vector3f Lo = sampleLight0(wo, scene, hitResult);
    // 再采样 BRDF
    Lo += sampleBRDF0(wo, scene, maxDepth, depth, hitResult);
    return Lo;
}

Vector3f PathTracer::sampleLight0(const Vector3f & wo, Scene * scene, const HitResult & hitResult) {
    Vector3f Lo(0, 0, 0);
    Material * material = hitResult.facet->getMaterial();
    for (Object * lit: scene->getLights()) {
        // 光源上采样一点
        float p1 = 0;
        Surface * facet = nullptr;
        Vector3f p = lit->sampleSurface(&p1, &facet);
        // d 代表采样方向 wi
        Vector3f d = p - hitResult.p;
        // 击中点到光源采样点的距离
        float r = d.length();
        if (r < 1) {
            continue;
        }
        // 归一化
        d /= r;
        // 如果背对光源应该是 0
        if (wo.dot(hitResult.n) * d.dot(hitResult.n) < 0) {
            continue;
        }
        // 否则面向光源，投射阴影光线
        Ray ray = {hitResult.p, d};
        HitResult result;
        if (scene->hitObject(ray, 1e-3, FLT_MAX, &result)) {
            // 如果击中点和被采样到的面片之间有其他面片挡住，则应当是 0
            if (result.facet != facet) {
                continue;
            }
            // 入射方向
            Vector3f wi = -d;
            // 按照 BRDF 采样到此方向的概率密度
            float p2 = material->getPdf(wi, wo, hitResult);
            // 计算 MIS 中的权重，使用平方策略
            float w = p1 * p1 / (p1 * p1 + p2 * p2);
            // 计算 fr
            Vector3f fr = material->getBRDF(wi, wo, hitResult);
            // 计算 Li
            Vector3f Li = facet->getMaterial()->getEmitting(wi, result);
            // 计算两个 cosine
            float cos1 = std::abs(wi.dot(hitResult.n));
            float cos2 = std::abs(wi.dot(result.n));
            // 累加到 Lo
            Lo += w * Li * fr * cos1 * cos2 / (p1 * r * r);
        }
    }
    return Lo;
}

Vector3f PathTracer::sampleBRDF0(const Vector3f & wo, Scene * scene, int maxDepth, int depth, const HitResult & hitResult) {
    float p2 = 0;
    Vector3f Lo(0, 0, 0);
    Material * material = hitResult.facet->getMaterial();
    Vector3f d = material->sampleBRDF(wo, &p2, hitResult);
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    // 如果采样的方向在表面以下，应当返回 0
    if (d.dot(n) < 0) {
        return {0, 0, 0};
    }
    // 下一条追踪光线
    Ray nextRay = {hitResult.p, d};
    HitResult nextHit;
    Vector3f wi = -d;
    if (scene->hitObject(nextRay, 1e-3, FLT_MAX, &nextHit)) {
        // 计算 fr
        Vector3f fr = material->getBRDF(wi, wo, hitResult);
        // 计算 cosine
        float cos = d.dot(n);
        // 看是否击中光源
        Surface * facet = nextHit.facet;
        Material * mat = facet->getMaterial();
        if (mat->isEmitting()) {
            // 如果击中的是光源
            float p1 = 0;
            Vector3f dist = (nextHit.p - hitResult.p);
            if (dist.dot(dist) >= 1) {
                p1 = facet->getObject()->getPdf(facet, nextHit.p);
            }
            // 计算 MIS 的权重
            float w = p2 * p2 / (p1 * p1 + p2 * p2);
            // 计算 Li
            Vector3f Li = mat->getEmitting(wi, hitResult);
            // 累加到 Lo
            Lo += w * Li * fr * cos / p2;
        } else {
            if (depth > maxDepth) {
                return {0, 0, 0};
            }
            // 计算 Li
            Vector3f Li = shade0(wi, scene, maxDepth, depth + 1, nextHit);
            // 累加到 Lo
            Lo += Li * fr * cos / p2;
        }
    }
    return Lo;
}
