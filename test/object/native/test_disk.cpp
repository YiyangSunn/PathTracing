#include <cfloat>
#include <cassert>
#include "object/native/Disk.h"
#include "material/Lambertian.h"
#include "test_helper.h"

int main() {
    Vector3d c(1, 1, 1);
    Vector3d o = Vector3d(-1, -1, -1);
    float r = 1.5f;
    Lambertian mat({0.2, 0.3, 0.4});
    Disk disk(c, o, r, &mat);

    assert_vector3d_equal(disk.getCenter(), c);
    assert_vector3d_equal(disk.getOrientation().cross(o), {0, 0, 0});
    assert_float_equal(disk.getRadius(), r);
    assert_box_equal(disk.getBoundingBox(), {-0.5, -0.5, -0.5, 2.5, 2.5, 2.5});

    HitRecord hitRec;
    for (int i = 0; i < 200; ++i) {
        Vector3d ro((float) drand48(), (float) drand48(), (float) drand48());
        Vector3d rd = Vector3d((float) drand48(), (float) drand48(), (float) drand48());
        if (disk.hit({ro, rd}, 1e-3, FLT_MAX, &hitRec)) {
            assert_vector3d_equal(hitRec.n.cross(o), {0, 0, 0});
            assert_float_equal(o.dot(hitRec.p - c), 0);
            assert_float_equal(hitRec.n.getLength(), 1);
            assert((hitRec.p - c).getLength() <= r);
            assert(hitRec.material == &mat);
        }
    }

    // test sampling on the surface
//    Vector3d s(0, 0, 0);
//    for (int i = 0; i < 300; ++i) {
//        Vector3d p = disk.samplePointOnSurface();
//        assert_float_equal((p - disk.getCenter()).getLength(), disk.getRadius());
//        assert_float_equal((p - disk.getCenter()).dot(disk.getOrientation()), 0);
//        s += p;
//    }
//    assert((s - disk.getCenter()).getLength() < 1e-2);

    return 0;
}
