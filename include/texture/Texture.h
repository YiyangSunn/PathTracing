#ifndef SIMPLE_RAY_TRACER_TEXTURE_H
#define SIMPLE_RAY_TRACER_TEXTURE_H

#include "util/Vector3f.h"

class Texture {

public:

    virtual Vector3f getValue(float u, float v, const Vector3f & p) = 0;

    virtual ~Texture() = default;

};

#endif //SIMPLE_RAY_TRACER_TEXTURE_H
