#ifndef SIMPLE_RAY_TRACER_MISAMPLER_H
#define SIMPLE_RAY_TRACER_MISAMPLER_H

#include "Renderer.h"
#include "util/math/Random.h"

class MISampler: public Renderer {

private:

    int spp;

    int nThreads;

    static Random randX;

    static Random randY;

    static void render0(Camera * camera, Scene * scene, ImageBuffer * im, int spp);

    static Vector3d trace0(const Ray & ray, Scene * scene);

    static Vector3d shade0(const Vector3d & wo, Scene * scene, const HitResult & hitResult);

    static Vector3d sampleLight0(const Vector3d & wo, Scene * scene, const HitResult & hitResult);

    static Vector3d sampleBRDF0(const Vector3d & wo, Scene * scene, const HitResult & hitResult);

public:

    MISampler(int spp = 50, int nThreads = 1);

    void render(Camera * camera, Scene * scene, ImageBuffer * im) override;

    virtual ~MISampler() = default;

};

#endif //SIMPLE_RAY_TRACER_MISAMPLER_H
