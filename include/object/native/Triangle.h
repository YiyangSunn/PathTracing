#ifndef SIMPLE_RAY_TRACER_TRIANGLE_H
#define SIMPLE_RAY_TRACER_TRIANGLE_H

#include "object/Hittable.h"

class Triangle: public Hittable {

private:

    // vertices of the triangle
    Vector3d p[3];

    // material of the triangle
    Material * material;

public:

    Triangle(const Vector3d & p1, const Vector3d & p2, const Vector3d & p3, Material * material);

    const Vector3d & operator[](int index) const;

    Vector3d & operator[](int index);

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~Triangle() override = default;

};

std::ostream & operator<<(std::ostream & out, const Triangle & t);

#endif //SIMPLE_RAY_TRACER_TRIANGLE_H
