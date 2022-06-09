#ifndef SIMPLE_RAY_TRACER_TRIANGLE_H
#define SIMPLE_RAY_TRACER_TRIANGLE_H

#include "Facet.h"
#include "util/math/Random.h"

class Triangle: public Facet {

private:

    // three vertices
    Vector3f vs[3];

    // three normals
    Vector3f ns[3];

    // three uv coordinates
    Vector3f uvs[3];

    Random randR1;

    Random randR2;

public:

    Triangle(
            const Vector3f & v1, const Vector3f & v2, const Vector3f & v3,
            const Vector3f & n1, const Vector3f & n2, const Vector3f & n3,
            const Vector3f & uv1, const Vector3f & uv2, const Vector3f & uv3,
            Object * parent, Material * material);

    bool hit(const Ray & rin, float tMin, float tMax, HitResult * hitResult) override;

    float getArea() override;

    Vector3f getSample(float * pdf) override;

    float getPdf(const Vector3f & p) override;

    AABB getBoundingBox() override;

    ~Triangle() override = default;

};

#endif //SIMPLE_RAY_TRACER_TRIANGLE_H
