#ifndef SIMPLE_RAY_TRACER_RAYTRACER_H
#define SIMPLE_RAY_TRACER_RAYTRACER_H

#include <vector>
#include "object/Hittable.h"
#include "camera/Camera.h"
#include "util/image/ImageBuffer.h"
#include "light/Light.h"

class RayTracer {

private:

    static void renderInThread(Camera * camera, Hittable * scene, const std::vector<Light *> & lights, ImageBuffer * im, int maxDepth, int sample);

    static Vector3d trace(const Ray & ray, Hittable * scene, const std::vector<Light *> & lights, int maxDepth, int depth = 0);

public:

    static void render(Camera * camera, Hittable * scene, const std::vector<Light *> & lights, ImageBuffer * im, int maxDepth, int totalSample, int nThreads = 1);

};

#endif //SIMPLE_RAY_TRACER_RAYTRACER_H
