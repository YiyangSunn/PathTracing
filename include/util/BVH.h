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

    AABB boundingBox;

public:

    BVHNode();

    explicit BVHNode(std::vector<Surface *> * surfaces, int i, int j);

    AABB getBoundingBox();

    virtual bool hitNode(const Ray & ray, float tMin, float tMax, HitResult * result);

    virtual ~BVHNode();

};

class BVHLeaf: public BVHNode {

private:

    Surface * surface;

public:

    explicit BVHLeaf(Surface * surf);

    bool hitNode(const Ray & ray, float tMin, float tMax, HitResult * result) override;

};

class BVH: public HitResolver {

private:

    BVHNode * root;

public:

    // build the tree on all the objects
    BVH();

    void build(const std::vector<Object *> & objects) override;

    bool resolveHit(const Ray & ray, float tMin, float tMax, HitResult * result) override;

    ~BVH() override;

};

#endif //SIMPLE_RAY_TRACER_BVH_H
