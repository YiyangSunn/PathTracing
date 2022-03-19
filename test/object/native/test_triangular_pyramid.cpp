#include <cfloat>
#include <cassert>
#include "object/native/TriangularPyramid.h"
#include "material/Lambertian.h"
#include "test_helper.h"

int main() {
    Lambertian mat({0.2, 0.2, 0.2});
    TriangularPyramid tp({0, 1.8, 0}, {1.1, 0, -1.1}, {-1.1, 0, -1.1}, {0, 0, 2.3}, &mat);
    Box box = tp.getBoundingBox();

    HitRecord hitRec;
    for (int i = 0; i < 200; ++i) {
        Vector3d o((float) drand48() * 10, (float) drand48() * 10, (float) drand48() * 10);
        Vector3d d = Vector3d((float) drand48(), (float) drand48(), (float) drand48()).normalize();
        if (tp.hit({o, d}, 1e-3, FLT_MAX, &hitRec)) {
            assert(box.contain(hitRec.p));
            assert_float_equal(hitRec.n.getLength(), 1.f);
        }
    }

    return 0;
}
