#ifndef SIMPLE_RAY_TRACER_MATERIAL_H
#define SIMPLE_RAY_TRACER_MATERIAL_H

#include "util/math/Vector3d.h"

// interface for all materials
class Material {

public:

    // compute the direction of the outgoing light, according to the incident light direction din,
    // the hit point pos and the surface normal noVec
    virtual bool scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout, Vector3d * attenuation) = 0;

    virtual Vector3d emit(float u, float v, const Vector3d & p) = 0;

    virtual ~Material() = default;

};

#endif //SIMPLE_RAY_TRACER_MATERIAL_H
