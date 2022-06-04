#include "material/Lambertian.h"
#include "util/math/Random.h"

Lambertian::Lambertian(Texture * texture): Material(texture) {

}

Vector3d Lambertian::getBRDF(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) {
    // 除以 pi
    return texture->getValue(hitResult.u, hitResult.v, hitResult.p) * 0.318310f;
}

Vector3d Lambertian::sampleBRDF(const Vector3d & wo, float * pdf, const HitResult & hitResult) {
//    *pdf = 0.159155f;
//    // 半球面上均匀采样
//    float r1 = randR1.randFloat(0, 1);
//    float r2 = randR2.randFloat(0, 1);
//    float cosi = 1 - r1;
//    float sine = std::sqrt(1 - cosi * cosi);
//    float phi = 6.28318f * r2;
//    float x = std::cos(phi) * sine;
//    float y = std::sin(phi) * sine;
//    float z = cosi;
//    Vector3d d(x, y, z);
//    // 检查采样点方向是否和表面法向相背
//    if (wo.dot(hitResult.n) * d.dot(hitResult.n) < 0) {
//        return -d;
//    }
//    return d;

    float r1 = randR1.randFloat(0, 1);
    float r2 = randR2.randFloat(0, 1);
    float phi = 2 * 3.14159f * r2;
    float sin_theta = std::sqrt(r1);
    float cos_theta = std::sqrt(1 - r1);
    float x = sin_theta * std::cos(phi);
    float y = sin_theta * std::sin(phi);
    float z = cos_theta;
    Vector3d v(x, y, z);

    *pdf = cos_theta / 3.14159f;

    Vector3d n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    // 计算把法向量 N 转到和 z 轴平行的矩阵
    // TODO 法向量已经和 z 轴平行
    x = n[0];
    y = n[1];
    z = n[2];
    float c = std::sqrt(x * x + y * y);
    float d = std::sqrt(c * c + z * z);
    cos_theta = y / c;
    sin_theta = x / c;
    float cos_phi = z / d, sin_phi = c / d;

    Vector3d m1(cos_theta, sin_theta * cos_phi, sin_theta * sin_phi);
    Vector3d m2(-sin_theta, cos_theta * cos_phi, cos_theta * sin_phi);
    Vector3d m3(0, -sin_phi, cos_phi);

    if (c < 1e-4) {
        float e = z < 0 ? -1 : 1;
        m1 = {e, 0, 0};
        m2 = {0, e, 0};
        m3 = {0, 0, e};
    }

    Vector3d wi(m1.dot(v), m2.dot(v), m3.dot(v));

    return wi;
}

float Lambertian::getPdf(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) {
    // 1 / (2 * pi)
//    return 0.159155f;
    return std::abs(wi.dot(hitResult.n)) / 3.14159f;
}

bool Lambertian::isEmitting() {
    return false;
}

Vector3d Lambertian::getEmitting(const Vector3d & wi, const HitResult & hitResult) {
    return {0, 0, 0};
}
