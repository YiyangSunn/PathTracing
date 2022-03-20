#ifndef SIMPLE_RAY_TRACER_RECTANGLE_H
#define SIMPLE_RAY_TRACER_RECTANGLE_H

#include "object/Hittable.h"

class Rectangle: public Hittable {

private:

    Vector3d c;

    Vector3d a;

    Vector3d b;

    Material * material;

public:

    // assume p0, p1, p2, p3 represents the four vertices of the rectangle, which must be
    // in counterclockwise order looked from outside, then c = p[0], a = p[1] - p[0], b = p[3] - p[0].
    Rectangle(const Vector3d & c, const Vector3d & a, const Vector3d & b, Material * material);

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    Vector3d getC() const;

    Vector3d getA() const;

    Vector3d getB() const;

    ~Rectangle() override = default;

};

std::ostream & operator<<(std::ostream & out, const Rectangle & rect);

#endif //SIMPLE_RAY_TRACER_RECTANGLE_H
