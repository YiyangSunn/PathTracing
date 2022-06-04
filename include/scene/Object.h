#ifndef SIMPLE_RAY_TRACER_OBJECT_H
#define SIMPLE_RAY_TRACER_OBJECT_H

#include <vector>
#include <random>
#include "surface/Facet.h"
#include "util/math/Random.h"

class Object {

protected:

    Random rng;

    std::vector<Facet *> surfaces;

public:

    Object() = default;

    void addSurface(Facet * facet);

    const std::vector<Facet *> & getSurfaces() const;

    Vector3d sampleSurface(float * pdf, Facet ** pFacet);

    float getPdf(Facet * surf, const Vector3d & p);

    virtual ~Object();

};

#endif //SIMPLE_RAY_TRACER_OBJECT_H
