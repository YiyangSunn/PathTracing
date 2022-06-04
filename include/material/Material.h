#ifndef SIMPLE_RAY_TRACER_MATERIAL_H
#define SIMPLE_RAY_TRACER_MATERIAL_H

#include "util/math/Vector3d.h"
#include "texture/Texture.h"
#include "surface/Facet.h"

class Material {

protected:

    Texture * texture;

public:

    explicit Material(Texture * texture): texture(texture) {}

    virtual Vector3d getBRDF(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) = 0;

    virtual Vector3d sampleBRDF(const Vector3d & wo, float * pdf, const HitResult & hitResult) = 0;

    virtual float getPdf(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) = 0;

    virtual bool isEmitting() = 0;

    virtual Vector3d getEmitting(const Vector3d & wi, const HitResult & hitResult) = 0;

    virtual ~Material() = default;

};

#endif //SIMPLE_RAY_TRACER_MATERIAL_H
