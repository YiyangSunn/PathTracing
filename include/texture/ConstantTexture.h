#ifndef SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H
#define SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H

#include "Texture.h"

class ConstantTexture: public Texture {

private:

    // the albedo which is constant everywhere
    Vector3d albedo;

public:

    ConstantTexture(const Vector3d & albedo);

    Vector3d getAlbedo() const;

    Vector3d getValue(float u, float v, const Vector3d & p) const override;

    ~ConstantTexture() override = default;

};

std::ostream & operator<<(std::ostream & out, const ConstantTexture & texture);

#endif //SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H
