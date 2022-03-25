#ifndef SIMPLE_RAY_TRACER_HITTABLE_H
#define SIMPLE_RAY_TRACER_HITTABLE_H

#include "util/math/Vector3d.h"
#include "material/Material.h"
#include "util/model/Box.h"

typedef struct HitRecord {

    // parameter of the incident light at p
    float t;

    float u;

    float v;

    // the hit point
    Vector3d p;

    // the normal vector at p
    Vector3d n;

    // the material of the surface
    Material * material;

    HitRecord() {
        t = u = v = -1;
        material = nullptr;
    }

} HitRecord;

// interface that must be implemented by all hittable objects
class Hittable {

public:

    // return true and fill the hitRec if hit the object
    virtual bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) = 0;

    // get the bounding box of the object
    virtual Box getBoundingBox() = 0;

    virtual ~Hittable() = default;

};

#endif //SIMPLE_RAY_TRACER_HITTABLE_H
