#include "material/Lambertian.h"
#include "util/FunctionUtil.h"
#include "util/Matrix3f.h"

Lambertian::Lambertian(Texture * texture): Material(texture) {

}

Vector3f Lambertian::getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    // 除以 pi
    return texture->getValue(hitResult.u, hitResult.v, hitResult.p) * 0.318310f;
}

Vector3f Lambertian::sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) {
    float r1 = randR1.randFloat(0, 1);
    float r2 = randR2.randFloat(0, 1);
    float phi = 2 * 3.14159f * r2;
    float sin_theta = std::sqrt(r1);
    float cos_theta = std::sqrt(1 - r1);
    float x = sin_theta * std::cos(phi);
    float y = sin_theta * std::sin(phi);
    float z = cos_theta;
    *pdf = cos_theta / 3.14159f;
    Vector3f n = wo.dot(hitResult.n) < 0 ? -hitResult.n : hitResult.n;
    Matrix3f rotT = FunctionUtil::worldToTangent(n).transposed();
    return rotT.dot({x, y, z});
}

float Lambertian::getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    return std::abs(wi.dot(hitResult.n)) / 3.14159f;
}

bool Lambertian::isEmitting() {
    return false;
}

Vector3f Lambertian::getEmitting(const Vector3f & wi, const HitResult & hitResult) {
    return {0, 0, 0};
}
