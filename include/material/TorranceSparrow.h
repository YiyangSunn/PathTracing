#ifndef SIMPLE_RAY_TRACER_TORRANCESPARROW_H
#define SIMPLE_RAY_TRACER_TORRANCESPARROW_H

#include "material/Material.h"
#include "util/math/Random.h"

class TorranceSparrow: public Material {

private:

    float alpha;

    Vector3d f0;

    Random randEp1;

    Random randEp2;

    // we'll use GGX here
    float D(const Vector3d & wh, const Vector3d & n) const;

    // we'll use smith height correlated masking-shadowing function
    float G(const Vector3d & wi, const Vector3d & wo, const Vector3d & n) const;

    // Fresnel item, we'll use schlick approximation
    Vector3d F(const Vector3d & wo, const Vector3d & wh);

public:

    TorranceSparrow(const Vector3d & f0, float roughness, Texture * texture);

    Vector3d getBRDF(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) override;

    Vector3d sampleBRDF(const Vector3d & wo, float * pdf, const HitResult & hitResult) override;

    float getPdf(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) override;

    bool isEmitting() override;

    Vector3d getEmitting(const Vector3d & wi, const HitResult & hitResult) override;

    ~TorranceSparrow() override = default;

};

#endif //SIMPLE_RAY_TRACER_TORRANCESPARROW_H
