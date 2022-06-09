#ifndef SIMPLE_RAY_TRACER_LIGHTSAMPLER_H
#define SIMPLE_RAY_TRACER_LIGHTSAMPLER_H

#include "Renderer.h"
#include "util/math/Random.h"

class LightSampler: public Renderer {

private:

    int spp;

    int nThreads;

    static Random randX;

    static Random randY;

    static void render0(Camera * camera, Scene * scene, ImageBuffer * im, int spp);

    static Vector3f trace0(const Ray & ray, Scene * scene);

    static Vector3f shade0(const Vector3f & wo, Scene * scene, const HitResult & hitResult);

    static Vector3f sampleLight0(const Vector3f & wo, Scene * scene, const HitResult & hitResult);

public:

    explicit LightSampler(int spp = 10, int nThreads = 1);

    void render(Camera * camera, Scene * scene, ImageBuffer * im) override;

    virtual ~LightSampler() = default;

};

#endif //SIMPLE_RAY_TRACER_LIGHTSAMPLER_H
