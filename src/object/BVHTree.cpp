#include <cfloat>
#include <algorithm>
#include "object/BVHTree.h"

BVHTree::BVHTree(std::vector<Hittable *> * objs): BVHTree(objs, 0, objs->size() - 1) {

}

BVHTree::BVHTree(std::vector<Hittable *> * objs, int i, int j) {
    if (i == j) {
        // only one object
        left = (*objs)[i];
        right = nullptr;
        leafChild = true;
    } else if (i == j - 1) {
        // only two objects
        left = (*objs)[i];
        right = (*objs)[j];
        leafChild = true;
    } else {
        // choose a random axis to split the objects
        int k = rand() % 3;
        std::sort(objs->begin() + i, objs->begin() + j + 1, [k](Hittable * h1, Hittable * h2) -> bool {
            Box b1 = h1->getBoundingBox();
            Box b2 = h2->getBoundingBox();
            return b1.getCenter()[k] < b2.getCenter()[k];
        });
        // construct recursively
        int m = i + (j - i) / 2;
        left = new BVHTree(objs, i, m);
        right = new BVHTree(objs, m + 1, j);
    }

    // get the surrounding box
    bigBox = left->getBoundingBox();
    if (right != nullptr) {
        Box boxRight = right->getBoundingBox();
        bigBox = {
                std::min(bigBox.getXMin(), boxRight.getXMin()),
                std::min(bigBox.getYMin(), boxRight.getYMin()),
                std::min(bigBox.getZMin(), boxRight.getZMin()),
                std::max(bigBox.getXMax(), boxRight.getXMax()),
                std::max(bigBox.getYMax(), boxRight.getYMax()),
                std::max(bigBox.getZMax(), boxRight.getZMax()),
        };
    }
}

bool BVHTree::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    if (bigBox.intersect(rin, tMin, tMax)) {
        // hit the big box, but may still miss the branches
        HitRecord hrec;
        if (!left->hit(rin, tMin, tMax, &hrec)) {
            if (right == nullptr || !right->hit(rin, tMin, tMax, &hrec)) {
                return false;
            } else {
                // only hit the right child
                *hitRec = hrec;
                return true;
            }
        } else {
            // hit the left child
            float t = hrec.t;
            *hitRec = hrec;
            if (right != nullptr && right->hit(rin, tMin, tMax, &hrec)) {
                // hit the right child too
                if (hrec.t < t) {
                    *hitRec = hrec;
                }
            }
            return true;
        }
    }
    return false;
}

Box BVHTree::getBoundingBox() {
    return bigBox;
}

BVHTree::~BVHTree() {
    // otherwise a leaf node
    if (!leafChild) {
        delete left;
        delete right;
        left = right = nullptr;
    }
}
