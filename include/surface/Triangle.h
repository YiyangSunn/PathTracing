#ifndef SIMPLE_RAY_TRACER_TRIANGLE_H
#define SIMPLE_RAY_TRACER_TRIANGLE_H

#include "Facet.h"
#include "util/math/Random.h"

class Triangle: public Facet {

private:

    // three vertices
    Vector3d vs[3];

    // three normals
    Vector3d ns[3];

    // three uv coordinates
    Vector3d uvs[3];

    Random randR1;

    Random randR2;

public:

    Triangle(
            const Vector3d & v1, const Vector3d & v2, const Vector3d & v3,
            const Vector3d & n1, const Vector3d & n2, const Vector3d & n3,
            const Vector3d & uv1, const Vector3d & uv2, const Vector3d & uv3,
            Object * parent, Material * material);

    bool hit(const Ray & rin, float tMin, float tMax, HitResult * hitResult) override;

    float getArea() override;

    Vector3d getSample(float * pdf) override;

    float getPdf(const Vector3d & p) override;

    Box getBoundingBox() override;

    ~Triangle() override = default;

};

#endif //SIMPLE_RAY_TRACER_TRIANGLE_H
