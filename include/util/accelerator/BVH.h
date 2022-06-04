#ifndef SIMPLE_RAY_TRACER_BVH_H
#define SIMPLE_RAY_TRACER_BVH_H

#include <vector>
#include "scene/Object.h"
#include "HitResolver.h"

class BVHNode {

private:

    BVHNode * left;

    BVHNode * right;

protected:

    Box boundingBox;

public:

    BVHNode();

    explicit BVHNode(std::vector<Facet *> * surfaces, int i, int j);

    Box getBoundingBox();

    virtual bool hitNode(const Ray & rin, float tMin, float tMax, HitResult * result);

    virtual ~BVHNode();

};

class BVHLeaf: public BVHNode {

private:

    Facet * surface;

public:

    explicit BVHLeaf(Facet * surf);

    bool hitNode(const Ray & rin, float tMin, float tMax, HitResult * result) override;

};

class BVH: public HitResolver {

private:

    BVHNode * root;

public:

    // build the tree on all the objects
    BVH();

    void build(const std::vector<Object *> & objects) override;

    bool resolveHit(const Ray & rin, float tMin, float tMax, HitResult * result) override;

    ~BVH() override;

};

#endif //SIMPLE_RAY_TRACER_BVH_H
