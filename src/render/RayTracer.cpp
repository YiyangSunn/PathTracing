#include <cfloat>
#include <thread>
#include <iostream>

#include "render/RayTracer.h"
#include "util/math/Random.h"
#include "material/Material.h"

void RayTracer::render(Camera * camera, Hittable * scene, const std::vector<Light *> & lights, ImageBuffer * im, int maxDepth, int totalSample, int nThreads) {
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
            workers[i] = new std::thread(RayTracer::renderInThread, camera, scene, lights, bufs[i], maxDepth, totalSample / nThreads);
        }
    }

    // run the rest work in current thread
    int restSample = totalSample - totalSample / nThreads * (nThreads - 1);
    renderInThread(camera, scene, lights, im, maxDepth, restSample);

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
void RayTracer::renderInThread(Camera * camera, Hittable * scene, const std::vector<Light *> & lights, ImageBuffer * im, int maxDepth, int sample) {
    int width = im->getWidth();
    int height = im->getHeight();
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= width; ++j) {
            Vector3d s(0, 0, 0);
            for (int k = 0; k < sample; ++k) {
                float x = (float) (j + 2 * drand48() - 1) / (float) (width + 1);
                // note that the y-axis is from bottom to top
                float y = 1.f - (float) (i + 2 * drand48() - 1) / (float) (height + 1);
                s += trace(camera->getRay(x, y), scene, lights, maxDepth, 0);
            }
            (*im)[i - 1][j - 1] = s;
        }
    }
}

Vector3d RayTracer::trace(const Ray & ray, Hittable * scene, const std::vector<Light *> & lights, int maxDepth, int depth) {
    HitRecord hitRec;
    if (depth < maxDepth && scene->hit(ray, 1e-3, FLT_MAX, &hitRec)) {
        Material * material = hitRec.obj->getMaterial();
        // 如果击中光源
        if (material->isEmitting()) {
            if (depth == 0) {
                // 从照相机发出的光线直接击中
                return material->emit();
            }
            // 否则是从其它物体来的光线，不重复计算
            return {0, 0, 0};
        }

        // 否则击中的是普通物体，先计算间接光照
        Vector3d din = ray.getDirection();
        Vector3d dout;
        Vector3d attenuation;
        Vector3d L_indir(0, 0, 0);
        if (material->scatter(din, hitRec.p, hitRec.n, &dout, &attenuation)) {
            Ray rout(hitRec.p, dout);
            L_indir += attenuation * trace(rout, scene, lights, maxDepth, depth + 1);
        }

        // 计算直接光照
        Vector3d L_dir(0, 0, 0);
        for (Light * li: lights) {
            // 在光源上采样一点
            Vector3d x = li->getSample();
            // 生成阴影光线
            Vector3d t = x - hitRec.p;
            // 检查是否面向光源
            Vector3d n = din.dot(hitRec.n) < 0 ? hitRec.n : -hitRec.n;
            if (n.dot(t) <= 0) {
                continue;
            }
            // 发送阴影光线
            Vector3d d = t.getNormalized();
            Ray shadowRay(hitRec.p, d);
            HitRecord rec;
            if (scene->hit(shadowRay, 1e-3, FLT_MAX, &rec)) {
                // 检查是否击中该光源
                if (rec.obj == li) {
                    // 累加到直接光照
                    Vector3d L_i = rec.obj->getMaterial()->emit();
                    // 检查距离大小
                    float distSquare = t.dot(t);
                    if (distSquare < 0.1) {
                        // 离这个光源很近
                        continue;
                    } else {
                        // 按照公式计算
                        L_dir += L_i * attenuation * std::abs(hitRec.n.dot(d)) * std::abs(rec.n.dot(d))
                                / distSquare / li->getPdf();
                    }
                }
            }
        }

        return L_dir + L_indir;
    }

//    Vector3d d = ray.getDirection();
//    float t = 0.5f * (d[1] + 1);
//    return (1 - t) * Vector3d(1, 1, 1) + t * Vector3d(0.5, 0.7, 1);

    // no light found
    return {0, 0, 0};
}
