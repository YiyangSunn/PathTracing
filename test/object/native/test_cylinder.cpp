#include <cfloat>
#include <cassert>
#include <iostream>
#include "object/native/Cylinder.h"
#include "material/Lambertian.h"
#include "test_helper.h"

int main() {
    Vector3d c(0.6, 0, -0.5);
    Vector3d o(1, 2, -3);
    float r = 1.3;
    float h = 2.2;
    Lambertian mat({0.2, 0.2, 0.3});
    Cylinder cylinder(c, o, r, h, &mat);

    assert_vector3d_equal(cylinder.getCenter(), c);
    assert_vector3d_equal(cylinder.getOrientation(), o.getNormalized());
    assert_float_equal(cylinder.getRadius(), r);
    assert_float_equal(cylinder.getHeight(), h);
    Box box = cylinder.getBoundingBox();

    HitRecord hitRec;
    for (int i = 0; i < 200; ++i) {
        Vector3d ro((float) drand48(), (float) drand48(), (float) drand48());
        Vector3d rd((float) drand48(), (float) drand48(), (float) drand48());
        if (cylinder.hit({ro, rd}, 1e-3, FLT_MAX, &hitRec)) {
            assert(box.contain(hitRec.p));
        }
    }

    cylinder = Cylinder({0, 0, 0}, {0, 0, -1}, 1.5, 2.4, &mat);
    assert(cylinder.hit({{0, 0, 1}, {0, 0, -1}}, 1e-3, FLT_MAX, &hitRec));
    assert_float_equal(hitRec.p.getLength(), 0);

    return 0;
}
