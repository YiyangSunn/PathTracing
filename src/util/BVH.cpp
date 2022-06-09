#include <algorithm>
#include "util/BVH.h"
#include "util/Random.h"

static Random rng;

BVH::BVH() {
    root = nullptr;
}

BVH::~BVH() {
    delete root;
}

void BVH::build(const std::vector<Object *> & objects) {
    delete root;
    std::vector<Surface *> surfaces;
    for (Object * obj: objects) {
        std::vector<Surface *> sufs = obj->getSurfaces();
        surfaces.insert(surfaces.end(), sufs.begin(), sufs.end());
    }
    root = new BVHNode(&surfaces, 0, (int) surfaces.size() - 1);
}

bool BVH::resolveHit(const Ray & ray, float tMin, float tMax, HitResult * result) {
    return root->hitNode(ray, tMin, tMax, result);
}

BVHNode::BVHNode() {
    left = nullptr;
    right = nullptr;
}

AABB BVHNode::getBoundingBox() {
    return boundingBox;
}

BVHNode::BVHNode(std::vector<Surface *> * surfaces, int i, int j) {
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
        std::sort(first, last,[k](Surface * s1, Surface * s2) -> bool {
            AABB b1 = s1->getBoundingBox();
            AABB b2 = s2->getBoundingBox();
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
        boundingBox = boundingBox.merged(right->getBoundingBox());
    }
}

bool BVHNode::hitNode(const Ray & ray, float tMin, float tMax, HitResult * result) {
    if (boundingBox.hit(ray, tMin, tMax)) {
        // hit the big box, but may still miss the branches
        HitResult tmpResult;
        if (!left->hitNode(ray, tMin, tMax, &tmpResult)) {
            if (right == nullptr || !right->hitNode(ray, tMin, tMax, &tmpResult)) {
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
            if (right != nullptr && right->hitNode(ray, tMin, tMax, &tmpResult)) {
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

BVHLeaf::BVHLeaf(Surface * surf) {
    surface = surf;
    boundingBox = surf->getBoundingBox();
}

bool BVHLeaf::hitNode(const Ray & ray, float tMin, float tMax, HitResult * result) {
    return surface->hit(ray, tMin, tMax, result);
}
