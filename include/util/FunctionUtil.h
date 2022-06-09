#ifndef SIMPLE_RAY_TRACER_FUNCTIONUTIL_H
#define SIMPLE_RAY_TRACER_FUNCTIONUTIL_H

#include "Matrix3f.h"

class FunctionUtil {

public:

    // 计算从世界坐标系变换到以法向为 z 轴正向的旋转矩阵
    static inline Matrix3f worldToTangent(const Vector3f & n) {
        float x = n[0], y = n[1], z = n[2];
        if (z > 0.999f) {
            return {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        } else if (z < -0.999f) {
            return {{-1, 0, 0},{0, -1, 0},{0, 0, -1}};
        }
        float c = std::sqrt(x * x + y * y);
        float cos_theta = y / c, sin_theta = x / c;
        float cos_phi = z, sin_phi = c;
        return {
                {cos_theta, -sin_theta, 0},
                {sin_theta * cos_phi, cos_theta * cos_phi, -sin_phi},
                {sin_theta * sin_phi, cos_theta * sin_phi, cos_phi}
        };
    }

};

#endif //SIMPLE_RAY_TRACER_FUNCTIONUTIL_H
