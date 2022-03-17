#include <cfloat>
#include "util/model/Box.h"

Box::Box(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
    bottomLeft = {xMin, yMin, zMin};
    topRight = {xMax, yMax, zMax};
}

Box::Box(const Vector3d & bottomLeft, const Vector3d & topRight) {
    this->bottomLeft = bottomLeft;
    this->topRight = topRight;
}

Vector3d Box::getBottomLeft() const {
    return bottomLeft;
}

Vector3d Box::getTopRight() const {
    return topRight;
}

float Box::getXMin() const {
    return bottomLeft[0];
}

float Box::getYMin() const {
    return bottomLeft[1];
}

float Box::getZMin() const {
    return bottomLeft[2];
}

float Box::getXMax() const {
    return topRight[0];
}

float Box::getYMax() const {
    return topRight[1];
}

float Box::getZMax() const {
    return topRight[2];
}

// we'll check if there exists a t between tMin and tMax so that
// r.origin + t * r.direction is inside the box
bool Box::intersect(const Ray & r, float tMin, float tMax) const {
    Vector3d o = r.getOrigin();
    Vector3d d = r.getDirection();
    float tLeft = FLT_MIN, tRight = FLT_MAX;
    for (int i = 0; i < 3; ++i) {
        float inv = 1.f / d[i];
        if (d[i] < 0) {
            tLeft = std::max(tLeft, (topRight[i] - o[i]) * inv);
            tRight = std::min(tRight, (bottomLeft[i] - o[i]) * inv);
        } else if (d[i] > 0) {
            tLeft = std::max(tLeft, (bottomLeft[i] - o[i]) * inv);
            tRight = std::min(tRight, (topRight[i] - o[i]) * inv);
        } else {
            if (o[i] < bottomLeft[i] || o[i] > topRight[i]) {
                return false;
            }
        }
        if (tLeft > tRight) {
            return false;
        }
    }
    return tLeft < tMax && tRight > tMin;
}

std::ostream & operator<<(std::ostream & out, const Box & box) {
    out << "Box{bottomLeft=" << box.getBottomLeft() << ",topRight=" << box.getTopRight() << "}";
    return out;
}
