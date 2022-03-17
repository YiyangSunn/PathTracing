#ifndef SIMPLE_RAY_TRACER_HITTABLELIST_H
#define SIMPLE_RAY_TRACER_HITTABLELIST_H

#include <vector>

#include "Hittable.h"

// represents a list of hittable objects, implement the hit function in
// a round-robin fashion
class HittableList: public Hittable {

private:

    std::vector<Hittable *> list;

public:

    explicit HittableList(std::vector<Hittable *> objs);

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~HittableList() override = default;

};

#endif //SIMPLE_RAY_TRACER_HITTABLELIST_H
