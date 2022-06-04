#ifndef SIMPLE_RAY_TRACER_FACET_H
#define SIMPLE_RAY_TRACER_FACET_H

#include "util/model/Ray.h"
#include "util/model/Box.h"

class HitResult;

class Object;

class Material;

class Facet {

private:

    // the object containing this facet
    Object * object;

    // material of the facet
    Material * material;

public:

    Facet(Object * obj, Material * mat): object(obj), material(mat) {};

    Object * getObject(){return object;}

    virtual bool hit(const Ray & rin, float tMin, float tMax, HitResult * hitResult) = 0;

    virtual float getArea() = 0;

    virtual Vector3d getSample(float * pdf) = 0;

    virtual float getPdf(const Vector3d & p) = 0;

    virtual Box getBoundingBox() = 0;

    virtual Material * getMaterial() {return material;}

    virtual ~Facet() = default;

};

class HitResult {

public:
    // parameter of the incident light at p
    float t;

    float u;

    float v;

    // the hit point
    Vector3d p;

    // the normal vector
    Vector3d n;

    // the hit surface
    Facet * facet;

    HitResult() {
        t = u = v = -1;
        p = Vector3d(0, 0, 0);
        n = Vector3d(0, 0, 0);
        facet = nullptr;
    }

};

#endif //SIMPLE_RAY_TRACER_FACET_H
