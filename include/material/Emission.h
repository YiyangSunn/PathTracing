#ifndef SIMPLE_RAY_TRACER_EMISSION_H
#define SIMPLE_RAY_TRACER_EMISSION_H

#include "Material.h"

class Emission: public Material {

public:

    explicit Emission(Texture * texture);

    Vector3f getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    Vector3f sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) override;

    float getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    bool isEmitting() override;

    Vector3f getEmitting(const Vector3f & wi, const HitResult & hitResult) override;

    ~Emission() override = default;

};

#endif //SIMPLE_RAY_TRACER_EMISSION_H
