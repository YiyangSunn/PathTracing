#ifndef SIMPLE_RAY_TRACER_OBJECT_H
#define SIMPLE_RAY_TRACER_OBJECT_H

#include <vector>
#include <random>
#include "surface/Surface.h"
#include "util/Random.h"

class Object {

protected:

    Random rng;

    std::vector<Surface *> surfaces;

public:

    Object() = default;

    inline void addSurface(Surface * surf) {
        surfaces.push_back(surf);
    }

    inline const std::vector<Surface *> & getSurfaces() const {
        return surfaces;
    }

    inline Vector3f sampleSurface(float * pdf, Surface ** pSurf) {
        int n = (int) surfaces.size();
        int i = rng.randInt(0, n);
        Surface * surf = surfaces[i];
        Vector3f p = surf->getSample(pdf);
        *pdf /= (float) n;
        *pSurf = surf;
        return p;
    }

    inline float getPdf(Surface * surf, const Vector3f & p) {
        int n = (int) surfaces.size();
        return 1.f / (float) n * surf->getPdf(p);
    }

    virtual ~Object() {
        for (Surface * facet: surfaces) {
            delete facet;
        }
    }

};

#endif //SIMPLE_RAY_TRACER_OBJECT_H
