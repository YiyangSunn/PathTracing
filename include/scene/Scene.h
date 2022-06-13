#ifndef SIMPLE_RAY_TRACER_SCENE_H
#define SIMPLE_RAY_TRACER_SCENE_H

#include <vector>
#include "Object.h"
#include "util/HitResolver.h"

class Scene {

private:

    std::vector<Object *> objects;

    std::vector<Object *> lights;

    HitResolver * hitResolver;

    // 背景色
    Vector3f background;

public:

    inline explicit Scene(HitResolver * resolver, const Vector3f & background = {0, 0, 0}) {
        hitResolver = resolver;
        this->background = background;
    }

    inline void setBackground(const Vector3f & color) { this->background = color; }

    inline const Vector3f & getBackground() const { return background; }

    inline void build() {
        hitResolver->build(objects);
    }

    inline void addObject(Object * obj) {
        objects.push_back(obj);
    }

    inline void addLight(Object * lit) {
        lights.push_back(lit);
        objects.push_back(lit);
    }

    inline const std::vector<Object *> & getLights() const { return lights; }

    inline bool hitObject(const Ray & rin, float tMin, float tMax, HitResult * result) {
        return hitResolver->resolveHit(rin, tMin, tMax, result);
    }

    virtual ~Scene() {
        for (Object * obj: objects) {
            delete obj;
        }
    }

};

#endif //SIMPLE_RAY_TRACER_SCENE_H
