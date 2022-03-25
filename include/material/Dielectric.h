#ifndef SIMPLE_RAY_TRACER_DIELECTRIC_H
#define SIMPLE_RAY_TRACER_DIELECTRIC_H

#include "Material.h"

class Dielectric: public Material {

private:

    // refractive index of the inside material
    float refIdxInside;

    // refractive index of the outside material
    float refIdxOutSide;

    // the texture of this material
    Vector3d albedo;

public:

    Dielectric();

    Dielectric(float refIdxInside, float refIdxOutside);

    explicit Dielectric(float refIdxInside, const Vector3d & albedo = {1.f, 1.f, 1.f}, float refIdxOutside = 1.f);

    bool scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout, Vector3d * attenuation) override;

    Vector3d emit(float u, float v, const Vector3d & p) override;

    Vector3d getAlbedo() const;

    float getRefIdxInside() const;

    float getRefIdxOutside() const;

    ~Dielectric() override = default;

};

std::ostream & operator<<(std::ostream & out, const Dielectric & mat);

#endif //SIMPLE_RAY_TRACER_DIELECTRIC_H
