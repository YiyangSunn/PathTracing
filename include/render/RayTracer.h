#ifndef SIMPLE_RAY_TRACER_RAYTRACER_H
#define SIMPLE_RAY_TRACER_RAYTRACER_H

#include "Renderer.h"
#include "object/Hittable.h"
#include "camera/Camera.h"

class RayTracer: public Renderer {

private:

    static void renderInThread(Camera * camera, Hittable * scene, ImageBuffer * im, int maxDepth, int sample);

    static Vector3d trace(const Ray & ray, Hittable * scene, int maxDepth, int depth = 0);

private:

    int maxDepth;

    // number of samples to collect around each pixel, the final color
    // is the average of all samples. A larger value would make it more
    // smooth while a smaller one would get it faster.
    int totalSample;

    // number of threads to run
    int nThreads;

public:

    RayTracer(int maxDepth = 10, int totalSample = 100, int nThreads = 1);

    void render(Camera * camera, Hittable * scene, ImageBuffer * im) override;

    int getMaxDepth() const;

    void setMaxDepth(int maxDepth);

    ~RayTracer() override = default;

};

#endif //SIMPLE_RAY_TRACER_RAYTRACER_H
