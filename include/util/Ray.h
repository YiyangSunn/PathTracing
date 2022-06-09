#ifndef SIMPLE_RAY_TRACER_RAY_H
#define SIMPLE_RAY_TRACER_RAY_H

#include "util/Vector3f.h"

class Ray {

private:

    Vector3f o;

    Vector3f d;

public:

    inline Ray(const Vector3f & o, const Vector3f & d) {
        this->o = o;
        this->d = d;
    }

    inline const Vector3f & getOrigin() const {
        return o;
    }

    inline const Vector3f & getDirection() const {
        return d;
    }

};

#endif //SIMPLE_RAY_TRACER_RAY_H
