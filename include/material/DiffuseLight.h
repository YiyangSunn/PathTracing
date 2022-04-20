#ifndef SIMPLE_RAY_TRACER_DIFFUSELIGHT_H
#define SIMPLE_RAY_TRACER_DIFFUSELIGHT_H

#include "Material.h"

class DiffuseLight: public Material {

private:

    // color of the light
    Vector3d albedo;

public:

    DiffuseLight(const Vector3d & albedo);

    Vector3d getAlbedo() const;

    bool scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout, Vector3d * attenuation) override;

    bool isEmitting() override;

    Vector3d emit() override;

    ~DiffuseLight() override = default;

};

std::ostream & operator<<(std::ostream & out, const DiffuseLight & light);

#endif //SIMPLE_RAY_TRACER_DIFFUSELIGHT_H
