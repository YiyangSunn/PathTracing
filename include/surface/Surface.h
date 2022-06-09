#ifndef SIMPLE_RAY_TRACER_SURFACE_H
#define SIMPLE_RAY_TRACER_SURFACE_H

#include "util/Ray.h"
#include "util/AABB.h"

class HitResult;

class Object;

class Material;

// 所有面片类的基类
class Surface {

private:

    // 此面片所属的对象
    Object * object;

    // 此面片的材质
    Material * material;

public:

    inline Surface(Object * obj, Material * mat): object(obj), material(mat) {};

    inline Object * getObject(){return object;}

    inline Material * getMaterial() {return material;}

    virtual bool hit(const Ray & ray, float tMin, float tMax, HitResult * hitResult) = 0;

    virtual float getArea() = 0;

    virtual Vector3f getSample(float * pdf) = 0;

    virtual float getPdf(const Vector3f & p) = 0;

    virtual AABB getBoundingBox() = 0;

    virtual void refresh() {};

    virtual ~Surface() = default;

};

class HitResult {

public:
    // parameter of the incident light at p
    float t;

    float u;

    float v;

    // the hit point
    Vector3f p;

    // the normal vector
    Vector3f n;

    // the hit surface
    Surface * facet;

    HitResult() {
        t = u = v = -1;
        p = Vector3f(0, 0, 0);
        n = Vector3f(0, 0, 0);
        facet = nullptr;
    }

};

#endif //SIMPLE_RAY_TRACER_SURFACE_H
