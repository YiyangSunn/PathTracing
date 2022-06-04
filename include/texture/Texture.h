#ifndef SIMPLE_RAY_TRACER_TEXTURE_H
#define SIMPLE_RAY_TRACER_TEXTURE_H

#include "util/math/Vector3d.h"

class Texture {

public:

    virtual Vector3d getValue(float u, float v, const Vector3d & p) = 0;

};

#endif //SIMPLE_RAY_TRACER_TEXTURE_H
