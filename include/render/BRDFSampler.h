#ifndef SIMPLE_RAY_TRACER_BRDFSAMPLER_H
#define SIMPLE_RAY_TRACER_BRDFSAMPLER_H

#include "Renderer.h"
#include "util/math/Random.h"

class BRDFSampler: public Renderer {

private:

    int spp;

    int nThreads;

    static Random randX;

    static Random randY;

    static void render0(Camera * camera, Scene * scene, ImageBuffer * im, int spp);

    static Vector3d trace0(const Ray & ray, Scene * scene);

    static Vector3d shade0(const Vector3d & wo, Scene * scene, const HitResult & hitResult);

    static Vector3d sampleBRDF0(const Vector3d & wo, Scene * scene, const HitResult & hitResult);

public:

    BRDFSampler(int spp = 100, int nThreads = 1);

    void render(Camera * camera, Scene * scene, ImageBuffer * im) override;

    virtual ~BRDFSampler() = default;

};

#endif //SIMPLE_RAY_TRACER_BRDFSAMPLER_H
