#ifndef SIMPLE_RAY_TRACER_LAMBERTIAN_H
#define SIMPLE_RAY_TRACER_LAMBERTIAN_H

#include "Material.h"

class Lambertian: public Material {

private:

    Vector3d albedo;

public:

    explicit Lambertian(const Vector3d & albedo);

    bool scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout, Vector3d * attenuation) override;

    Vector3d emit(float u, float v, const Vector3d & p) override;

    Vector3d getAlbedo() const;

    void setAlbedo(const Vector3d & albedo);

};

std::ostream & operator<<(std::ostream & out, const Material & material);

#endif //SIMPLE_RAY_TRACER_LAMBERTIAN_H
