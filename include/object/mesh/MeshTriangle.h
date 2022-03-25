#ifndef SIMPLE_RAY_TRACER_MESHTRIANGLE_H
#define SIMPLE_RAY_TRACER_MESHTRIANGLE_H

#include "object/Hittable.h"

typedef struct {
    // the coordinate
    Vector3d p;

    // the normal
    Vector3d n;

} MeshPoint;

// triangle used in mesh models
class MeshTriangle: public Hittable {

private:

    // three vertices
    MeshPoint v[3];

    // the material
    Material * material;

public:

    MeshTriangle(const MeshPoint & mp1, const MeshPoint & mp2, const MeshPoint & mp3, Material * material);

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    MeshPoint operator[](int index) const;

    MeshPoint & operator[](int index);

    ~MeshTriangle() override = default;

};

std::ostream & operator<<(std::ostream & out, const MeshPoint & mp);

std::ostream & operator<<(std::ostream & out, const MeshTriangle & mt);

#endif //SIMPLE_RAY_TRACER_MESHTRIANGLE_H
