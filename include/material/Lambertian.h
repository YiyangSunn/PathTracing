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

    Vector3d getBRDF(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) override;

    Vector3d sampleBRDF(const Vector3d & wo, float * pdf, const HitResult & hitResult) override;

    float getPdf(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) override;

    bool isEmitting() override;

    Vector3d getEmitting(const Vector3d & wi, const HitResult & hitResult) override;

    ~Lambertian() override = default;

};

#endif //SIMPLE_RAY_TRACER_LAMBERTIAN_H
