#ifndef SIMPLE_RAY_TRACER_GLOSSYBRDF_H
#define SIMPLE_RAY_TRACER_GLOSSYBRDF_H

#include "material/Material.h"
#include "util/Random.h"

class GlossyBRDF: public Material {

private:

    double a;

    double a2;

    Vector3f f0;

    Random randEp1;

    Random randEp2;

    // GGX Distribution
    inline float D(float NoH) const {
        double t = NoH * NoH * (a2 - 1) + 1;
        return (float) (0.318310 * a2 / (t * t));
    }

    // Smith Height-Correlated Masking and Shadowing Function
    inline float G(float NoL, float NoV) const {
        double sql = std::sqrt(a2 + (1 - a2) * NoL * NoL);
        double sqv = std::sqrt(a2 + (1 - a2) * NoV * NoV);
        return (float) (2 * NoL * NoV / (NoV * sql + NoL * sqv));
    }

    // Schlick Approximation
    inline Vector3f F(float HoO) {
        return f0 + (1 - f0) * std::pow(1.f - HoO, 5.f);
    }

public:

    GlossyBRDF(const Vector3f & f0, float roughness, Texture * texture);

    Vector3f getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    Vector3f sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) override;

    float getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    bool isEmitting() override;

    Vector3f getEmitting(const Vector3f & wi, const HitResult & hitResult) override;

    ~GlossyBRDF() override = default;

};

#endif //SIMPLE_RAY_TRACER_GLOSSYBRDF_H
