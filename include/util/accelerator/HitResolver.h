#ifndef SIMPLE_RAY_TRACER_HITRESOLVER_H
#define SIMPLE_RAY_TRACER_HITRESOLVER_H

#include <vector>

#include "util/model/Ray.h"
#include "surface/Facet.h"

// interface
class HitResolver {

public:

    virtual void build(const std::vector<Object *> & objects) = 0;

    virtual bool resolveHit(const Ray & rin, float tMin, float tMax, HitResult * result) = 0;

    virtual ~HitResolver() = default;

};

#endif //SIMPLE_RAY_TRACER_HITRESOLVER_H
