#ifndef SIMPLE_RAY_TRACER_TEXTURE_H
#define SIMPLE_RAY_TRACER_TEXTURE_H

#include "util/math/Vector3d.h"

// top interface for all texture classes
class Texture {

public:

    // get the value（typically albedo） at hit point p according to UV coordinate
    virtual Vector3d getValue(float u, float v, const Vector3d & p) const = 0;

    virtual ~Texture() = 0;

};

#endif //SIMPLE_RAY_TRACER_TEXTURE_H
