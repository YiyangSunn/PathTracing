#include <cfloat>
#include <thread>
#include <iostream>

#include "render/RayTracer.h"
#include "util/math/Random.h"

RayTracer::RayTracer(int maxDepth, int totalSample, int nThreads) {
    this->maxDepth = maxDepth;
    this->totalSample = totalSample;
    this->nThreads = nThreads;
}

int RayTracer::getMaxDepth() const {
    return maxDepth;
}

void RayTracer::setMaxDepth(int maxDepth) {
    this->maxDepth = maxDepth;
}

void RayTracer::render(Camera * camera, Hittable * scene, ImageBuffer * im) {
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
            workers[i] = new std::thread(RayTracer::renderInThread, camera, scene, bufs[i], maxDepth, totalSample / nThreads);
        }
    }

    // run the rest work in current thread
    int restSample = totalSample - totalSample / nThreads * (nThreads - 1);
    renderInThread(camera, scene, im, maxDepth, restSample);

    if (nThreads > 1 && workers != nullptr) {
        // wait for other threads
        for (int i = 0; i < nThreads - 1; ++i) {
            workers[i]->join();
            delete workers[i];
            workers[i] = nullptr;
        }
        delete workers;
        workers = nullptr;

        // reduce the results
        for (int k = 0; k < nThreads - 1; ++k) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    (*im)[i][j] += (*bufs[k])[i][j];
                }
            }
            delete bufs[k];
            bufs[k] = nullptr;
        }
        delete bufs;
        bufs = nullptr;
    }

    // average
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            (*im)[i][j] /= (float) totalSample;
        }
    }
}

// in-thread rendering
void RayTracer::renderInThread(Camera * camera, Hittable * scene, ImageBuffer * im, int maxDepth, int sample) {
    int width = im->getWidth();
    int height = im->getHeight();
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= width; ++j) {
            Vector3d s(0, 0, 0);
            for (int k = 0; k < sample; ++k) {
                float x = (float) (j + 2 * drand48() - 1) / (float) (width + 1);
                // note that the y-axis is from bottom to top
                float y = 1.f - (float) (i + 2 * drand48() - 1) / (float) (height + 1);
                s = s + trace(camera->getRay(x, y), scene, maxDepth, 0);
            }
            (*im)[i - 1][j - 1] = s;
        }
    }
}

Vector3d RayTracer::trace(const Ray & ray, Hittable * scene, int maxDepth, int depth) {
    HitRecord hitRec;
    if (depth < maxDepth && scene->hit(ray, 1e-3, FLT_MAX, &hitRec)) {
        Material * material = hitRec.material;
        Vector3d dout;
        if (material->scatter(ray.getDirection(), hitRec.p, hitRec.n, &dout)) {
            Ray rout(hitRec.p, dout);
            return material->getAttenuation() * trace(rout, scene, maxDepth, depth + 1);
        } else {
            // entirely absorbed by the material
            return {0, 0, 0};
        }
    }
    // an background color for now
    Vector3d d = ray.getDirection();
    float t = 0.5f * (d[1] + 1);
    return (1 - t) * Vector3d(1, 1, 1) + t * Vector3d(0.5, 0.7, 1);
}
