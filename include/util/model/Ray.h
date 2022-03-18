#ifndef SIMPLE_RAY_TRACER_RAY_H
#define SIMPLE_RAY_TRACER_RAY_H

#include "util/math/Vector3d.h"

class Ray {

private:

    Vector3d origin;

    Vector3d direction;

public:

    Ray(const Vector3d & origin, const Vector3d & direction);

    Vector3d getOrigin() const;

    Vector3d getDirection() const;

    void setOrigin(const Vector3d & origin);

    void setDirection(const Vector3d & direction);

};

std::ostream & operator<<(std::ostream & out, const Ray & r);

#endif //SIMPLE_RAY_TRACER_RAY_H
