#include <cfloat>
#include "render/RayTracer.h"
#include "util/math/Random.h"

RayTracer::RayTracer(Camera * camera, Hittable * scene, int maxDepth, int sample) {
    this->camera = camera;
    this->scene = scene;
    this->maxDepth = maxDepth;
    this->sample = sample;
}

void RayTracer::render(ImageBuffer * im) {
    int width = im->getWidth();
    int height = im->getHeight();
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= width; ++j) {
            Vector3d s(0, 0, 0);
            for (int k = 0; k < sample; ++k) {
                float x = (float) (j + 2 * drand48() - 1) / (float) (width + 1);
                // note that the y-axis is from bottom to top
                float y = 1.f - (float) (i + 2 * drand48() - 1) / (float) (height + 1);
                s = s + trace(camera->getRay(x, y));
            }
            (*im)[i - 1][j - 1] = s / (float) sample;
        }
    }
}

int RayTracer::getMaxDepth() const {
    return maxDepth;
}

void RayTracer::setMaxDepth(int maxDepth) {
    this->maxDepth = maxDepth;
}

Vector3d RayTracer::trace(const Ray & ray, int depth) {
    HitRecord hitRec;
    if (depth < maxDepth && scene->hit(ray, 1e-3, FLT_MAX, &hitRec)) {
        Material * material = hitRec.material;
        Vector3d dout;
        if (material->scatter(ray.getDirection(), hitRec.p, hitRec.n, &dout)) {
            Ray rout(hitRec.p, dout);
            return material->getAttenuation() * trace(rout, depth + 1);
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
