#include <thread>
#include <cfloat>
#include "render/LightSampler.h"
#include "util/math/Random.h"
#include "material/Material.h"

Random LightSampler::randX;

Random LightSampler::randY;

LightSampler::LightSampler(int spp, int nThreads) {
    this->spp = spp;
    this->nThreads = nThreads;
}

void LightSampler::render(Camera * camera, Scene * scene, ImageBuffer * im) {
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
                    LightSampler::render0, camera, scene, bufs[i], spp / nThreads);
        }
    }

    // run the rest work in current thread
    int rest = spp - spp / nThreads * (nThreads - 1);
    render0(camera, scene, im, rest);

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

void LightSampler::render0(Camera * camera, Scene * scene, ImageBuffer * im, int spp) {
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
                color += trace0(camera->getRay(x, y), scene);
            }
            (*im)[i - 1][j - 1] = color;
        }
    }
}

Vector3f LightSampler::trace0(const Ray & ray, Scene * scene) {
    HitResult hitResult;
    if (scene->hitObject(ray, 1e-3, FLT_MAX, &hitResult)) {
        // 计算击中点的颜色
        return shade0(-ray.getDirection(), scene, hitResult);
    }
    // 逸出场景
    return {0, 0, 0};
}

Vector3f LightSampler::shade0(const Vector3f & wo, Scene * scene, const HitResult & hitResult) {
    Material * material = hitResult.facet->getMaterial();
    // 如果击中光源（发光材质），只有一个 L_e 项
    if (material->isEmitting()) {
        return material->getEmitting(wo, hitResult);
    }
    // 否则击中一个普通物体，采样光源
    return sampleLight0(wo, scene, hitResult);
}

Vector3f LightSampler::sampleLight0(const Vector3f & wo, Scene * scene, const HitResult & hitResult) {
    Vector3f Lo(0, 0, 0);
    Material * material = hitResult.facet->getMaterial();
    for (Object * lit: scene->getLights()) {
        // 光源上采样一点
        float p1 = 0;
        Facet * facet = nullptr;
        Vector3f p = lit->sampleSurface(&p1, &facet);
        // d 代表采样方向 -wi
        Vector3f d = p - hitResult.p;
        // 计算击中点到光源采样点的距离平方
        float rsq = d.dot(d);
        // 如果背对光源应该是 0
        if (wo.dot(hitResult.n) * d.dot(hitResult.n) < 0) {
            continue;
        }
        // 否则面向光源，投射阴影光线
        Ray r = {hitResult.p, d.normalized()};
        HitResult result;
        if (scene->hitObject(r, 1e-3, FLT_MAX, &result)) {
            // 如果击中点和被采样到的面片之间有其他面片挡住，则应当是 0
            if (result.facet != facet) {
                continue;
            }
            // 入射方向
            Vector3f wi = -r.getDirection();
            // 计算 fr
            Vector3f fr = material->getBRDF(wi, wo, hitResult);
            // 计算 Li
            Vector3f Li = facet->getMaterial()->getEmitting(wi, result);
            // 计算两个 cosine
            float cos1 = std::abs(wi.dot(hitResult.n));
            float cos2 = std::abs(wi.dot(result.n));
            // 累加到 Lo
            Lo += Li * fr * cos1 * cos2 / (p1 * rsq);
        }
    }
    return Lo;
}
