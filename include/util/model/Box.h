#ifndef SIMPLE_RAY_TRACER_BOX_H
#define SIMPLE_RAY_TRACER_BOX_H

#include "util/model/Ray.h"

class Box {

private:

    Vector3d bottomLeft;

    Vector3d topRight;

public:

    Box(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);

    Box(const Vector3d & bottomLeft, const Vector3d & topRight);

    Vector3d getBottomLeft() const;

    Vector3d getTopRight() const;

    float getXMin() const;

    float getYMin() const;

    float getZMin() const;

    float getXMax() const;

    float getYMax() const;

    float getZMax() const;

    // return true if rin intersects the box
    bool intersect(const Ray & r, float tMin, float tMax) const;

};

std::ostream & operator<<(std::ostream & out, const Box & box);

#endif //SIMPLE_RAY_TRACER_BOX_H
