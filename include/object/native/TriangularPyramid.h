#ifndef SIMPLE_RAY_TRACER_TRIANGULARPYRAMID_H
#define SIMPLE_RAY_TRACER_TRIANGULARPYRAMID_H

#include "object/Hittable.h"
#include "object/native/Triangle.h"

class TriangularPyramid: public Hittable {

private:

    // the four vertices
    Vector3d p[4];

    // the four sides
    Triangle * sides[4]{};

public:

    TriangularPyramid(const Vector3d & p1, const Vector3d & p2, const Vector3d & p3, const Vector3d & p4, Material * material);

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    const Triangle & operator[](int index) const;

    Triangle & operator[](int index);

    TriangularPyramid & operator=(const TriangularPyramid & tp);

    ~TriangularPyramid() override;

};

std::ostream & operator<<(std::ostream & out, const TriangularPyramid & tp);

#endif //SIMPLE_RAY_TRACER_TRIANGULARPYRAMID_H
