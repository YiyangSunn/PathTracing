#include <cmath>
#include "surface/Triangle.h"
#include "util/math/Random.h"

Triangle::Triangle(const Vector3f & v1, const Vector3f & v2, const Vector3f & v3, const Vector3f & n1,
                   const Vector3f & n2, const Vector3f & n3, const Vector3f & uv1, const Vector3f & uv2,
                   const Vector3f & uv3, Object * parent, Material * material): Facet(parent, material) {
    vs[0] = v1; vs[1] = v2; vs[2] = v3;
    ns[0] = n1; ns[1] = n2; ns[2] = n3;
    uvs[0] = uv1; uvs[1] = uv2; uvs[2] = uv3;
}

bool Triangle::hit(const Ray & rin, float tMin, float tMax, HitResult * hitResult) {
    const Vector3f o = rin.getOrigin();
    const Vector3f d = rin.getDirection();
    Vector3f E1 = vs[1] - vs[0];
    Vector3f E2 = vs[2] - vs[0];
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
        hitResult->n = (1 - x - y) * ns[0] + x * ns[1] + y * ns[2];
        hitResult->u = (1 - x - y) * uvs[0][0] + x * uvs[1][0] + y * uvs[2][0];
        hitResult->v = (1 - x - y) * uvs[0][1] + x * uvs[1][1] + y * uvs[2][1];
        return true;
    }
    return false;
}

float Triangle::getArea() {
    Vector3f E1 = vs[1] - vs[0];
    Vector3f E2 = vs[2] - vs[0];
    return E1.cross(E2).length() / 2.f;
}

Vector3f Triangle::getSample(float * pdf) {
    *pdf = 1.f / getArea();
    Vector3f E1 = vs[1] - vs[0];
    Vector3f E2 = vs[2] - vs[0];
    Vector3f N = E1.cross(E2);
    // 计算把法向量 N 转到和 z 轴平行的矩阵
    // TODO 法向量已经和 z 轴平行
    float x = N[0], y = N[1], z = N[2];
    float c = std::sqrt(x * x + y * y);
    float d = std::sqrt(c * c + z * z);
    float cos_theta = y / c, sin_theta = x / c;
    float cos_phi = z / d, sin_phi = c / d;
    Vector3f m1(cos_theta, -sin_theta, 0);
    Vector3f m2(sin_theta * cos_phi, cos_theta * cos_phi, -sin_phi);
    Vector3f m3(sin_theta * sin_phi, cos_theta * sin_phi, cos_phi);

    if (c < 1e-4) {
        float e = z < 0 ? -1 : 1;
        m1 = {e, 0, 0};
        m2 = {0, e, 0};
        m3 = {0, 0, e};
    }

    // 计算旋转后的 ABC 三点的坐标
    Vector3f A = {m1.dot(vs[0]), m2.dot(vs[0]), m3.dot(vs[0])};
    Vector3f B = {m1.dot(vs[1]), m2.dot(vs[1]), m3.dot(vs[1])};
    Vector3f C = {m1.dot(vs[2]), m2.dot(vs[2]), m3.dot(vs[2])};
    // 在平行于 XOY 平面的三角形内均匀采样
    float r1 = randR1.randFloat(0, 1);
    float r2 = randR2.randFloat(0, 1);
    Vector3f P = (1 - std::sqrt(r1)) * A + std::sqrt(r1) * (1 - r2) * B + r2 * std::sqrt(r1) * C;
    // 再转回原来的位置
    Vector3f m4(m1[0], m2[0], m3[0]);
    Vector3f m5(m1[1], m2[1], m3[1]);
    Vector3f m6(m1[2], m2[2], m3[2]);
    return {m4.dot(P), m5.dot(P), m6.dot(P)};
}

float Triangle::getPdf(const Vector3f & p) {
    return 1.f / getArea();
}

AABB Triangle::getBoundingBox() {
    Vector3f bottomLeft = vs[0];
    Vector3f topRight = vs[0];
    for (int i = 1; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            bottomLeft[j] = std::min(bottomLeft[j], vs[i][j]);
            topRight[j] = std::max(topRight[j], vs[i][j]);
        }
    }
    return {bottomLeft, topRight};
}
