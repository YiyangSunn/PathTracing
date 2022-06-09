#ifndef SIMPLE_RAY_TRACER_TORRANCESPARROW_H
#define SIMPLE_RAY_TRACER_TORRANCESPARROW_H

#include "material/Material.h"
#include "util/math/Random.h"

class TorranceSparrow: public Material {

private:

    float alpha;

    Vector3f f0;

    Random randEp1;

    Random randEp2;

    // we'll use GGX here
    float D(const Vector3f & wh, const Vector3f & n) const;

    // we'll use smith height correlated masking-shadowing function
    float G(const Vector3f & wi, const Vector3f & wo, const Vector3f & n) const;

    // Fresnel item, we'll use schlick approximation
    Vector3f F(const Vector3f & wo, const Vector3f & wh);

public:

    TorranceSparrow(const Vector3f & f0, float roughness, Texture * texture);

    Vector3f getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    Vector3f sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) override;

    float getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) override;

    bool isEmitting() override;

    Vector3f getEmitting(const Vector3f & wi, const HitResult & hitResult) override;

    ~TorranceSparrow() override = default;

};

#endif //SIMPLE_RAY_TRACER_TORRANCESPARROW_H
