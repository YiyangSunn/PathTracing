#ifndef SIMPLE_RAY_TRACER_AABB_H
#define SIMPLE_RAY_TRACER_AABB_H

#include "util/Ray.h"
#include <cfloat>

class AABB {

private:

    Vector3f bottomLeft;

    Vector3f topRight;

public:

    inline AABB() = default;

    inline AABB(const Vector3f & bottomLeft, const Vector3f & topRight) {
        this->bottomLeft = bottomLeft;
        this->topRight = topRight;
    }

    inline Vector3f getCenter() const {
        return (bottomLeft + topRight) / 2;
    }

    // 返回此包围盒和另一个包围盒合并的结果
    inline AABB merged(const AABB & aabb) const {
        return {
            Vector3f::min(bottomLeft, aabb.bottomLeft),
            Vector3f::max(topRight, aabb.topRight)
        };
    }

    // 返回光线 ray 是否击中此包围盒
    bool hit(const Ray & ray, float tMin, float tMax) const {
        const Vector3f & o = ray.getOrigin();
        const Vector3f & d = ray.getDirection();
        float tLeft = FLT_MIN;
        float tRight = FLT_MAX;
        for (int i = 0; i < 3; ++i) {
            float inv = 1.f / d[i];
            if (d[i] < 0) {
                tLeft = std::max(tLeft, (topRight[i] - o[i]) * inv);
                tRight = std::min(tRight, (bottomLeft[i] - o[i]) * inv);
            } else if (d[i] > 0) {
                tLeft = std::max(tLeft, (bottomLeft[i] - o[i]) * inv);
                tRight = std::min(tRight, (topRight[i] - o[i]) * inv);
            } else {
                if (o[i] < bottomLeft[i] || o[i] > topRight[i]) {
                    return false;
                }
            }
            if (tLeft > tRight) {
                return false;
            }
        }
        return tLeft < tMax && tRight > tMin;
    }

};

#endif //SIMPLE_RAY_TRACER_AABB_H
