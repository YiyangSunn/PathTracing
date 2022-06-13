#include <thread>
#include <cfloat>
#include "render/BRDFSampler.h"
#include "material/Material.h"

Random BRDFSampler::randX;

Random BRDFSampler::randY;

BRDFSampler::BRDFSampler(int spp, int nThreads) {
    this->spp = spp;
    this->nThreads = nThreads;
}

void BRDFSampler::render(Camera * camera, Scene * scene, ImageBuffer * im) {
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
                    BRDFSampler::render0, camera, scene, bufs[i], spp / nThreads);
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

void BRDFSampler::render0(Camera * camera, Scene * scene, ImageBuffer * im, int spp) {
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

Vector3f BRDFSampler::trace0(const Ray & ray, Scene * scene) {
    HitResult hitResult;
    if (scene->hitObject(ray, 1e-3, FLT_MAX, &hitResult)) {
        // 计算击中点的颜色
        return shade0(-ray.getDirection(), scene, hitResult);
    }
    // 逸出场景
    return scene->getBackground();
}

Vector3f BRDFSampler::shade0(const Vector3f & wo, Scene * scene, const HitResult & hitResult) {
    Material * material = hitResult.facet->getMaterial();
    // 如果击中光源（发光材质），只有一个 L_e 项
    if (material->isEmitting()) {
        return material->getEmitting(wo, hitResult);
    }
    // 否则击中一个普通物体，采样 BRDF
    return sampleBRDF0(wo, scene, hitResult);
}

Vector3f BRDFSampler::sampleBRDF0(const Vector3f & wo, Scene * scene, const HitResult & hitResult) {
    float p2 = 0;
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
    if (scene->hitObject(nextRay, 1e-3, FLT_MAX, &nextHit)) {
        // 只有击中光源才有颜色
        Material * nextMat = nextHit.facet->getMaterial();
        if (nextMat->isEmitting()) {
            Vector3f wi = -d;
            // 计算 Li
            Vector3f Li = nextMat->getEmitting(wi, hitResult);
            // 计算 fr
            Vector3f fr = material->getBRDF(wi, wo, hitResult);
            // 计算 cosine
            float cos = d.dot(n);
            // 累加到 Lo
            return Li * fr * cos / p2;
        }
    }
    return {0, 0, 0};
}
