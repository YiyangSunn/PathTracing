#ifndef SIMPLE_RAY_TRACER_LAMBERTIAN_H
#define SIMPLE_RAY_TRACER_LAMBERTIAN_H

#include "Material.h"
#include "util/math/Random.h"

class Lambertian: public Material {

private:

    Random randR1;

    Random randR2;

public:

    explicit Lambertian(Texture * texture);

    Vector3f getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    Vector3f sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) override;

    float getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    bool isEmitting() override;

    Vector3f getEmitting(const Vector3f & wi, const HitResult & hitResult) override;

    ~Lambertian() override = default;

};

#endif //SIMPLE_RAY_TRACER_LAMBERTIAN_H
