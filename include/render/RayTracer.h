#ifndef SIMPLE_RAY_TRACER_RAYTRACER_H
#define SIMPLE_RAY_TRACER_RAYTRACER_H

#include "Renderer.h"
#include "object/Hittable.h"
#include "camera/Camera.h"

class RayTracer: public Renderer {

private:

    int maxDepth;

    // number of samples to collect around each pixel, the final color
    // is the average of all samples. A larger value would make it more
    // smooth while a smaller one would get it faster.
    int sample;

    Camera * camera;

    Hittable * scene;

    Vector3d trace(const Ray & ray, int depth = 0);

public:

    RayTracer(Camera * camera, Hittable * scene, int maxDepth = 10, int sample = 100);

    void render(ImageBuffer * im) override;

    int getMaxDepth() const;

    void setMaxDepth(int maxDepth);

    ~RayTracer() override = default;

};

#endif //SIMPLE_RAY_TRACER_RAYTRACER_H
