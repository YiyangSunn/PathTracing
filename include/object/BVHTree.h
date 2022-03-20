#ifndef SIMPLE_RAY_TRACER_BVHTREE_H
#define SIMPLE_RAY_TRACER_BVHTREE_H

#include <vector>

#include "Hittable.h"

class BVHTree: public Hittable {

private:

    // whether the two children are leaf nodes
    bool leafChild;

    // the box surrounding the BVH Tree
    Box bigBox;

    // left child
    Hittable * left{};

    // right child
    Hittable * right{};

public:

    // build the tree on all the objects
    explicit BVHTree(std::vector<Hittable *> * objs);

    //  build the tree on objects in range [i, j)
    BVHTree(std::vector<Hittable *> * objs, int i, int j);

    BVHTree(const BVHTree & tree) = delete;

    BVHTree & operator=(const BVHTree & tree) = delete;

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~BVHTree() override;

};

#endif //SIMPLE_RAY_TRACER_BVHTREE_H
