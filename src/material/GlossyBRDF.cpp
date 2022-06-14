#include <cmath>
#include "material/GlossyBRDF.h"
#include "util/FunctionUtil.h"

GlossyBRDF::GlossyBRDF(float roughness, Texture * texture): Material(texture) {
    this->a = roughness * roughness;
    this->a2 = a * a;
//    this->f0 = f0;
}

Vector3f GlossyBRDF::getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    // 宏观法向
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    float NoI = -(wi.dot(n));
    float NoO = wo.dot(n);
    // 微观法向
    Vector3f h = (wo - wi).normalize();
    float HoO = wo.dot(h);
    float NoH = h.dot(n);
    return F(HoO, hitResult) * G(NoI, NoO) * D(NoH) / (4 * NoI * NoO);
}

Vector3f GlossyBRDF::sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) {
    // 宏观法向
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    // 假设法向量为 z 轴正向进行采样
    float xi_1 = randEp1.randFloat(0, 1);
    float xi_2 = randEp2.randFloat(0, 1);
    float phi = 6.28319f * xi_2;
    float cos_theta_2 = (1 - xi_1) / (float) (1 + (a2 - 1) * xi_1);
    float sin_theta = std::sqrt(1 - cos_theta_2);
    float x = sin_theta * std::cos(phi);
    float y = sin_theta * std::sin(phi);
    float z = std::sqrt(cos_theta_2);
    // 转回原来的位置
    Vector3f h = FunctionUtil::worldToTangent(n).transposed().dot({x, y, z});
    // 计算采样的 wi 方向
    float cos_o = wo.dot(h);
    Vector3f wi = 2 * cos_o * h - wo;
    // 计算 wi 的概率密度
    float NoH = h.dot(n);
    *pdf = D(NoH) * NoH / (4 * cos_o);
    return wi;
}

float GlossyBRDF::getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    Vector3f h = (wo - wi).normalize();
    float NoH = h.dot(n);
    return D(NoH) * NoH / (4 * wo.dot(h));
}

bool GlossyBRDF::isEmitting() {
    return false;
}

Vector3f GlossyBRDF::getEmitting(const Vector3f & wi, const HitResult & hitResult) {
    return {0, 0, 0};
}
