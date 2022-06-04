#ifndef SIMPLE_RAY_TRACER_PATH_TRACER_H
#define SIMPLE_RAY_TRACER_PATH_TRACER_H

#include "Renderer.h"
#include "util/math/Random.h"

class PathTracer: public Renderer {

private:

    // sample per pixel
    int spp;

    // russian roulette
    int maxDepth;

    // how many threads to use
    int nThreads;

    static Random randX;

    static Random randY;

    static void render0(Camera * camera, Scene * scene, ImageBuffer * im, int spp, int maxDepth);

    static Vector3d trace0(const Ray & ray, Scene * scene, int maxDepth);

    static Vector3d shade0(const Vector3d & wo, Scene * scene, int maxDepth, int depth, const HitResult & hitResult);

    static Vector3d sampleLight0(const Vector3d & wo, Scene * scene, const HitResult & hitResult);

    static Vector3d sampleBRDF0(const Vector3d & wo, Scene * scene, int maxDepth, int depth, const HitResult & hitResult);

public:

    explicit PathTracer(int spp = 30, int maxDepth = 10, int nThreads = 1);

    void render(Camera * camera, Scene * scene, ImageBuffer * im) override;

};

#endif //SIMPLE_RAY_TRACER_PATH_TRACER_H
