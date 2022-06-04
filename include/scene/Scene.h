#ifndef SIMPLE_RAY_TRACER_SCENE_H
#define SIMPLE_RAY_TRACER_SCENE_H

#include <vector>
#include "Object.h"
#include "util/accelerator/HitResolver.h"

class Scene {

private:

    std::vector<Object *> objects;

    std::vector<Object *> lights;

    HitResolver * hitResolver;

public:

    explicit Scene(HitResolver * resolver);

    void build();

    void addObject(Object * obj);

    void addLight(Object * lit);

    const std::vector<Object *> & getLights() const;

    bool hitObject(const Ray & rin, float tMin, float tMax, HitResult * result);

    virtual ~Scene();

};

#endif //SIMPLE_RAY_TRACER_SCENE_H
