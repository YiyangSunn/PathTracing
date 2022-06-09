#include <cmath>
#include "material/TorranceSparrow.h"
#include "util/math/Random.h"

TorranceSparrow::TorranceSparrow(const Vector3f & f0, float roughness, Texture * texture): Material(texture) {
    this->alpha = roughness * roughness;
    this->f0 = f0;
}

Vector3f TorranceSparrow::getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    float cos_theta_i = -(wi.dot(n));
    float cos_theta_o = wo.dot(n);
    Vector3f wh = (wo - wi).normalize();
    return F(wo, wh) * G(wi, wo, n) * D(wh, n) / (4 * cos_theta_i * cos_theta_o);
}

Vector3f TorranceSparrow::F(const Vector3f & wo, const Vector3f & wh) {
    return f0 + (1 - f0) * (float) std::pow(1.f - wh.dot(wo), 5);
}

float TorranceSparrow::G(const Vector3f & wi, const Vector3f & wo, const Vector3f & n) const {
    float cos1 = -(wi.dot(n));
    float cos2 = wo.dot(n);
    float cos1_2 = cos1 * cos1;
    float cos2_2 = cos2 * cos2;
    float a2 = alpha * alpha;
    float sq1 = std::sqrt(a2 + (1 - a2) * cos1_2);
    float sq2 = std::sqrt(a2 + (1 - a2) * cos2_2);
    return 2 * cos1 * cos2 / (cos2 * sq1 + cos1 * sq2);
}

float TorranceSparrow::D(const Vector3f & wh, const Vector3f & n) const {
    float a2 = alpha * alpha;
    float cos = wh.dot(n);
    float t = cos * cos * (a2 - 1) + 1;
    return 0.318310f * a2 / (t * t);
}

Vector3f TorranceSparrow::sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) {
    // 计算把法向量转到和 z 轴平行的矩阵的转置矩阵
    // TODO 法向量已经和 z 轴平行
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    float x = n[0], y = n[1], z = n[2];
    float c = std::sqrt(x * x + y * y);
    float d = std::sqrt(c * c + z * z);
    float cos_theta = y / c, sin_theta = x / c;
    float cos_phi = z / d, sin_phi = c / d;
    Vector3f m1(cos_theta, sin_theta * cos_phi, sin_theta * sin_phi);
    Vector3f m2(-sin_theta, cos_theta * cos_phi, cos_theta * sin_phi);
    Vector3f m3(0, -sin_phi, cos_phi);

    if (c < 1e-4) {
        float e = z < 0 ? -1 : 1;
        m1 = {e, 0, 0};
        m2 = {0, e, 0};
        m3 = {0, 0, e};
    }

    // 假设法向量和 z 轴平行进行采样
    float epsilon_1 = randEp1.randFloat(0, 1);
    float epsilon_2 = randEp2.randFloat(0, 1);
    float phi = 6.28319f * epsilon_2;
    float a2 = alpha * alpha;
    float cos_theta_2 = (1 - epsilon_1) / (1 + (a2 - 1) * epsilon_1);
    sin_theta = std::sqrt(1 - cos_theta_2);
    x = sin_theta * std::cos(phi);
    y = sin_theta * std::sin(phi);
    z = std::sqrt(cos_theta_2);
    Vector3f v(x, y, z);

    // 转回原来的位置
    Vector3f wh(m1.dot(v), m2.dot(v), m3.dot(v));

    // 计算采样的 wi 方向
    float cos_o = wh.dot(wo);
    Vector3f wi = 2 * cos_o * wh - wo;

    // 计算 wi 的概率密度
//    float cos_NoH = wh.dot(n);
//    float cos_NoI = wi.dot(n);
//    float sin_NoH = std::sqrt(1 - cos_NoH * cos_NoH);
//    float sin_NoI = std::sqrt(1 - cos_NoI * cos_NoI);
    *pdf = D(wh, n) * wh.dot(n) / (4 * wi.dot(wh));
//    *pdf = D(wh, n) * sin_NoH * cos_NoH / (2 * sin_NoI);

    return wi;
}

float TorranceSparrow::getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    Vector3f wh = (wo - wi).normalize();
    return D(wh, n) * wh.dot(n) / (-4 * wi.dot(wh));
//    throw std::logic_error("should not be called now");
}

bool TorranceSparrow::isEmitting() {
    return false;
}

Vector3f TorranceSparrow::getEmitting(const Vector3f & wi, const HitResult & hitResult) {
    return {0, 0, 0};
}
