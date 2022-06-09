#ifndef SIMPLE_RAY_TRACER_TRIANGLE_H
#define SIMPLE_RAY_TRACER_TRIANGLE_H

#include "Surface.h"
#include "util/Random.h"
#include "util/Matrix3f.h"

class Triangle: public Surface {

private:

    // 顶点坐标
    Vector3f vs[3];

    // 顶点处法向量
    Vector3f vns[3];

    // 顶点处贴图坐标
    Vector3f vts[3];

    Random randR1;

    Random randR2;

    // 缓存的数据
    float area{};

    float pdf{};

    Vector3f E1;

    Vector3f E2;

    Vector3f N;

    Vector3f zAlignedA;

    Vector3f zAlignedB;

    Vector3f zAlignedC;

    Matrix3f rotT;

public:

    Triangle(const Vector3f & v1, const Vector3f & v2, const Vector3f & v3,
             const Vector3f & vn1, const Vector3f & vn2, const Vector3f & vn3,
             const Vector3f & vt1, const Vector3f & vt2, const Vector3f & vt3,
             Object * object, Material * material);

    bool hit(const Ray & ray, float tMin, float tMax, HitResult * hitResult) override;

    float getArea() override;

    Vector3f getSample(float * ppdf) override;

    float getPdf(const Vector3f & p) override;

    AABB getBoundingBox() override;

    void refresh() override;

    ~Triangle() override = default;

};

#endif //SIMPLE_RAY_TRACER_TRIANGLE_H
