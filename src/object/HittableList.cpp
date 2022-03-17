#include "object/HittableList.h"

HittableList::HittableList(std::vector<Hittable *> objs) {
    list.insert(list.end(), objs.begin(), objs.end());
}

bool HittableList::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    // store the smallest t
    float t = -1;
    // for temporary usage
    HitRecord rec;
    for (Hittable * obj: list) {
        // hit the object
        if (obj->hit(rin, tMin, tMax, &rec)) {
            // if it's the first hit or the intersection is closer
            if (t < 0 || rec.t < t) {
                t = rec.t;
                *hitRec = rec;
            }
        }
    }
    return t > tMin && t < tMax;
}

Box HittableList::getBoundingBox() {
    if (list.empty()) {
        return {0, 0, 0, 0, 0, 0};
    }
    Box box = list[0]->getBoundingBox();
    Vector3d bottomLeft = box.getBottomLeft();
    Vector3d topRight = box.getTopRight();
    for (Hittable * obj: list) {
        box = obj->getBoundingBox();
        for (int i = 0; i < 3; ++i) {
            bottomLeft[i] = std::min(bottomLeft[i], box.getBottomLeft()[i]);
            topRight[i] = std::max(topRight[i], box.getTopRight()[i]);
        }
    }
    return {bottomLeft, topRight};
}
