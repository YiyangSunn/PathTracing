#include <cmath>
#include "surface/Triangle.h"
#include "util/FunctionUtil.h"

Triangle::Triangle(const Vector3f & v1, const Vector3f & v2, const Vector3f & v3,
                   const Vector3f & vn1, const Vector3f & vn2, const Vector3f & vn3,
                   const Vector3f & vt1, const Vector3f & vt2, const Vector3f & vt3,
                   Object * parent, Material * material): Surface(parent, material) {
    vs[0] = v1; vs[1] = v2; vs[2] = v3;
    vns[0] = vn1; vns[1] = vn2; vns[2] = vn3;
    vts[0] = vt1; vts[1] = vt2; vts[2] = vt3;
    Triangle::refresh();
}

bool Triangle::hit(const Ray & ray, float tMin, float tMax, HitResult * hitResult) {
    const Vector3f & o = ray.getOrigin();
    const Vector3f & d = ray.getDirection();
    Vector3f T = o - vs[0];
    Vector3f P = d.cross(E2);
    Vector3f Q = T.cross(E1);
    float PE1 = P.dot(E1);
    if (std::abs(PE1) > 1e-4) {
        float t = Q.dot(E2) / PE1;
        if (t <= tMin || t >= tMax) {
            return false;
        }
        float x = P.dot(T) / PE1;
        if (x < 0 || x > 1) {
            return false;
        }
        float y = Q.dot(d) / PE1;
        if (y < 0 || x + y > 1) {
            return false;
        }
        hitResult->t = t;
        hitResult->p = o + t * d;
        hitResult->facet = this;
        hitResult->n = (1 - x - y) * vns[0] + x * vns[1] + y * vns[2];
        hitResult->n.normalize();
        hitResult->u = (1 - x - y) * vts[0][0] + x * vts[1][0] + y * vts[2][0];
        hitResult->v = (1 - x - y) * vts[0][1] + x * vts[1][1] + y * vts[2][1];
        return true;
    }
    return false;
}

Vector3f Triangle::getSample(float * ppdf) {
    *ppdf = pdf;
    // 在平行于 XOY 平面的三角形内均匀采样
    float xi_1 = randR1.randFloat(0, 1);
    float xi_2 = randR2.randFloat(0, 1);
    float sqxi_1 = std::sqrt(xi_1);
    Vector3f P = (1 - sqxi_1) * zAlignedA + sqxi_1 * (1 - xi_2) * zAlignedB + xi_2 * sqxi_1 * zAlignedC;
    // 再转回原来的位置
    return rotT.dot(P);
}

float Triangle::getArea() {
    return area;
}

float Triangle::getPdf(const Vector3f & p) {
    return pdf;
}

AABB Triangle::getBoundingBox() {
    return {
            Vector3f::min(vs[0], Vector3f::min(vs[1], vs[2])),
            Vector3f::max(vs[0], Vector3f::max(vs[1], vs[2]))
    };
}

void Triangle::refresh() {
    // 两条边和法向量
    E1 = vs[1] - vs[0];
    E2 = vs[2] - vs[0];
    // 中间结果
    Vector3f TN = E1.cross(E2);
    // 面积
    area = TN.length() / 2;
    // 法向量
    N = TN / (2 * area);
    // 概率密度
    pdf = 1.f / area;
    // 旋转矩阵
    Matrix3f m = FunctionUtil::worldToTangent(N);
    // 逆矩阵
    rotT = m.transposed();
    zAlignedA = m.dot(vs[2]);
    zAlignedB = m.dot(vs[0]);
    zAlignedC = m.dot(vs[1]);
}
