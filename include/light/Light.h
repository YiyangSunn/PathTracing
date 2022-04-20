#ifndef SIMPLE_RAY_TRACER_LIGHT_H
#define SIMPLE_RAY_TRACER_LIGHT_H

#include "util/math/Vector3d.h"
#include "object/Hittable.h"

class Light: public Hittable {

public:

    explicit Light(Material * material);

    virtual Vector3d getSample() = 0;

    virtual float getPdf() = 0;

};

#endif //SIMPLE_RAY_TRACER_LIGHT_H
