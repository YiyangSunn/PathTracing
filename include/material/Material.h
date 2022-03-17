#ifndef SIMPLE_RAY_TRACER_MATERIAL_H
#define SIMPLE_RAY_TRACER_MATERIAL_H

#include "util/math/Vector3d.h"

// interface for all materials
class Material {

public:

    // compute the direction of the outgoing light, according to the incident light direction din,
    // the hit point p and the surface normal n
    virtual bool scatter(const Vector3d & din, const Vector3d & p, const Vector3d & n, Vector3d * dout) = 0;

    // use attenuation * color to get the effect of the material
    virtual Vector3d getAttenuation() = 0;

    virtual ~Material() = default;

};

#endif //SIMPLE_RAY_TRACER_MATERIAL_H
