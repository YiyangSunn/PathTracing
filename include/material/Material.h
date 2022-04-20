#ifndef SIMPLE_RAY_TRACER_MATERIAL_H
#define SIMPLE_RAY_TRACER_MATERIAL_H

#include "util/math/Vector3d.h"

// interface for all materials
class Material {

public:

    virtual bool scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout, Vector3d * attenuation) = 0;

    virtual bool isEmitting();

    virtual Vector3d emit();

    virtual ~Material() = default;

};

#endif //SIMPLE_RAY_TRACER_MATERIAL_H
