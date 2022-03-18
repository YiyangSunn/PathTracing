#include "camera/DefocusBlur.h"
#include "util/math/Random.h"

DefocusBlur::DefocusBlur(const Vector3d & pos, const Vector3d & view, const Vector3d & up, float dist, float width,
                         float height, float aperture): Perspective(pos, view, up, dist, width, height) {

    this->diskRadius = aperture / 2;
}

// look at the same target on the image plane, but from a random
// position on the disk of radius aperture at e
Ray DefocusBlur::getRay(float x, float y) {
    Vector3d p = Random::randomInUnitDisk();
    p *= diskRadius;
    Vector3d offset = p[0] * u + p[1] * v;
    Vector3d rd = - d * w + (x - 0.5f) * width * u + (y - 0.5f) * height * v - offset;
    return {e + offset, rd.normalize()};
}
