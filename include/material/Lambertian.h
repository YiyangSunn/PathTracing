#ifndef SIMPLE_RAY_TRACER_LAMBERTIAN_H
#define SIMPLE_RAY_TRACER_LAMBERTIAN_H

#include "Material.h"

class Lambertian: public Material {

private:

    Vector3d albedo;

public:

    explicit Lambertian(const Vector3d & albedo);

    bool scatter(const Vector3d & din, const Vector3d & p, const Vector3d & n, Vector3d * dout) override;

    Vector3d getAttenuation() override;

    Vector3d getAlbedo() const;

    void setAlbedo(const Vector3d & albedo);

};

std::ostream & operator<<(std::ostream & out, const Material & material);

#endif //SIMPLE_RAY_TRACER_LAMBERTIAN_H
