#include "texture/ConstantTexture.h"

ConstantTexture::ConstantTexture(const Vector3d & albedo) {
    this->albedo = albedo;
}

Vector3d ConstantTexture::getAlbedo() const {
    return albedo;
}

Vector3d ConstantTexture::getValue(float u, float v, const Vector3d & p) const {
    return albedo;
}

std::ostream & operator<<(std::ostream & out, const ConstantTexture & texture) {
    out << "ConstantTexture{albedo=" << texture.getAlbedo() << "}";
    return out;
}
