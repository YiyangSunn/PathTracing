#include <algorithm>
#include "util/accelerator/BVH.h"
#include "util/math/Random.h"

static Random rng;

BVH::BVH() {
    root = nullptr;
}

BVH::~BVH() {
    delete root;
}

void BVH::build(const std::vector<Object *> & objects) {
    delete root;
    std::vector<Facet *> surfaces;
    for (Object * obj: objects) {
        std::vector<Facet *> sufs = obj->getSurfaces();
        surfaces.insert(surfaces.end(), sufs.begin(), sufs.end());
    }
    root = new BVHNode(&surfaces, 0, (int) surfaces.size() - 1);
}

bool BVH::resolveHit(const Ray & rin, float tMin, float tMax, HitResult * result) {
    return root->hitNode(rin, tMin, tMax, result);
}

BVHNode::BVHNode() {
    left = nullptr;
    right = nullptr;
}

Box BVHNode::getBoundingBox() {
    return boundingBox;
}

BVHNode::BVHNode(std::vector<Facet *> * surfaces, int i, int j) {
    if (i == j) {
        // only one scene
        left = new BVHLeaf((*surfaces)[i]);
        right = nullptr;
    } else if (i == j - 1) {
        // only two objects
        left = new BVHLeaf((*surfaces)[i]);
        right = new BVHLeaf((*surfaces)[j]);
    } else {
        // choose a random axis to split the objects
        int k = rng.randInt(0, 3);
        auto first = surfaces->begin() + i;
        auto last = surfaces->begin() + j + 1;
        std::sort(first, last,[k](Facet * s1, Facet * s2) -> bool {
            Box b1 = s1->getBoundingBox();
            Box b2 = s2->getBoundingBox();
            return b1.getCenter()[k] < b2.getCenter()[k];
        });
        // construct recursively
        int m = i + (j - i) / 2;
        left = new BVHNode(surfaces, i, m);
        right = new BVHNode(surfaces, m + 1, j);
    }

    // get the surrounding box
    boundingBox = left->getBoundingBox();
    if (right != nullptr) {
        Box boxRight = right->getBoundingBox();
        boundingBox = Box{
                std::min(boundingBox.getXMin(), boxRight.getXMin()),
                std::min(boundingBox.getYMin(), boxRight.getYMin()),
                std::min(boundingBox.getZMin(), boxRight.getZMin()),
                std::max(boundingBox.getXMax(), boxRight.getXMax()),
                std::max(boundingBox.getYMax(), boxRight.getYMax()),
                std::max(boundingBox.getZMax(), boxRight.getZMax()),
        };
    }
}

bool BVHNode::hitNode(const Ray & rin, float tMin, float tMax, HitResult * result) {
    if (boundingBox.intersect(rin, tMin, tMax)) {
        // hit the big box, but may still miss the branches
        HitResult tmpResult;
        if (!left->hitNode(rin, tMin, tMax, &tmpResult)) {
            if (right == nullptr || !right->hitNode(rin, tMin, tMax, &tmpResult)) {
                return false;
            } else {
                // only hit the right child
                *result = tmpResult;
                return true;
            }
        } else {
            // hit the left child
            float t = tmpResult.t;
            *result = tmpResult;
            if (right != nullptr && right->hitNode(rin, tMin, tMax, &tmpResult)) {
                // hit the right child too
                if (tmpResult.t < t) {
                    *result = tmpResult;
                }
            }
            return true;
        }
    }
    return false;
}

BVHNode::~BVHNode() {
    delete left;
    delete right;
}

BVHLeaf::BVHLeaf(Facet * surf) {
    surface = surf;
    boundingBox = surf->getBoundingBox();
}

bool BVHLeaf::hitNode(const Ray & rin, float tMin, float tMax, HitResult * result) {
    return surface->hit(rin, tMin, tMax, result);
}
