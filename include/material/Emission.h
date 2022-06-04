#ifndef SIMPLE_RAY_TRACER_EMISSION_H
#define SIMPLE_RAY_TRACER_EMISSION_H

#include "Material.h"

class Emission: public Material {

public:

    explicit Emission(Texture * texture);

    Vector3d getBRDF(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) override;

    Vector3d sampleBRDF(const Vector3d & wo, float * pdf, const HitResult & hitResult) override;

    float getPdf(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) override;

    bool isEmitting() override;

    Vector3d getEmitting(const Vector3d & wi, const HitResult & hitResult) override;

    ~Emission() override = default;

};

#endif //SIMPLE_RAY_TRACER_EMISSION_H
