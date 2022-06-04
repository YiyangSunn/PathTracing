#include "scene/Scene.h"

Scene::Scene(HitResolver * resolver) {
    hitResolver = resolver;
}

void Scene::build() {
    hitResolver->build(objects);
}

void Scene::addObject(Object * obj) {
    objects.push_back(obj);
}

void Scene::addLight(Object * lit) {
    lights.push_back(lit);
    objects.push_back(lit);
}

const std::vector<Object *> & Scene::getLights() const {
    return lights;
}

bool Scene::hitObject(const Ray & rin, float tMin, float tMax, HitResult * result) {
    return hitResolver->resolveHit(rin, tMin, tMax, result);
}

Scene::~Scene() {
    for (Object * obj: objects) {
        delete obj;
    }
}
