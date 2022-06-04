#include "scene/Object.h"
#include "util/math/Random.h"

void Object::addSurface(Facet * surf) {
    surfaces.push_back(surf);
}

const std::vector<Facet *> & Object::getSurfaces() const {
    return surfaces;
}

Vector3d Object::sampleSurface(float * pdf, Facet ** pFacet) {
    int n = (int) surfaces.size();
    int i = rng.randInt(0, n);
    Facet * facet = surfaces[i];
    Vector3d p = facet->getSample(pdf);
    *pdf /= (float) n;
    *pFacet = facet;
    return p;
}

float Object::getPdf(Facet * facet, const Vector3d & p) {
    int n = (int) surfaces.size();
    return 1.f / (float) n * facet->getPdf(p);
}

Object::~Object() {
    for (Facet * facet: surfaces) {
        delete facet;
    }
}
