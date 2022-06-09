#ifndef SIMPLE_RAY_TRACER_MATERIAL_H
#define SIMPLE_RAY_TRACER_MATERIAL_H

#include "util/Vector3f.h"
#include "texture/Texture.h"
#include "surface/Surface.h"

class Material {

protected:

    Texture * texture;

public:

    explicit Material(Texture * texture): texture(texture) {}

    virtual Vector3f getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) = 0;

    virtual Vector3f sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) = 0;

    virtual float getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) = 0;

    virtual bool isEmitting() = 0;

    virtual Vector3f getEmitting(const Vector3f & wi, const HitResult & hitResult) = 0;

    virtual ~Material() = default;

};

#endif //SIMPLE_RAY_TRACER_MATERIAL_H
