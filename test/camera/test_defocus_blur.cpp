#include <cassert>
#include "camera/DefocusBlur.h"

int main() {
    Vector3d p(1.1, 1.1, 1.1);
    Vector3d v(1.3, -1.2, 2.1);
    Vector3d up(0, 1, 0);
    float dist = 1.3f;
    float width = 15;
    float height = 20;
    DefocusBlur camera(p, v, up, dist, width, height, 2.2);

    Vector3d s(0, 0, 0);
    for (int i = 0; i < 200; ++i) {
        auto x = (float) drand48();
        auto y = (float) drand48();
        Ray r = camera.getRay(x, y);
        s += r.getOrigin();
    }
    assert((s / 200 - p).getLength() < 1e-1);

    return 0;
}
