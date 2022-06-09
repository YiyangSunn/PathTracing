#ifndef SIMPLE_RAY_TRACER_MATRIX3F_H
#define SIMPLE_RAY_TRACER_MATRIX3F_H

#include "Vector3f.h"

class Matrix3f {

private:

    // 三个行向量
    Vector3f rVecs[3];

public:

    inline Matrix3f() = default;

    inline Matrix3f(const Vector3f & rv1, const Vector3f & rv2, const Vector3f & rv3) {
        rVecs[0] = rv1;
        rVecs[1] = rv2;
        rVecs[2] = rv3;
    }

    inline Vector3f dot(const Vector3f & v) const {
        return {rVecs[0].dot(v), rVecs[1].dot(v), rVecs[2].dot(v)};
    }

    inline Matrix3f transposed() const {
        return {
                {rVecs[0][0], rVecs[1][0], rVecs[2][0]},
                {rVecs[0][1], rVecs[1][1], rVecs[2][1]},
                {rVecs[0][2], rVecs[1][2], rVecs[2][2]}
        };
    }

};

#endif //SIMPLE_RAY_TRACER_MATRIX3F_H
