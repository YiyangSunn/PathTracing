#include <cfloat>
#include <cassert>
#include <iostream>
#include "object/native/Tube.h"
#include "material/Lambertian.h"
#include "test_helper.h"

int main() {
    Vector3d c(1, 0.5, 2);
    Vector3d o(0, 1, 0);
    float r = 1.5;
    float h = 2.4;
    Lambertian mat({0.2, 0.3, 0.4});
    Tube tube(c, o, r, h, &mat);

    assert_float_equal(tube.getOrientation().getLength(), 1);
    assert_vector3d_equal(tube.getCenter(), c);
    assert_float_equal(tube.getHeight(), h);
    assert_float_equal(tube.getRadius(), r);
    Box box = tube.getBoundingBox();

    HitRecord hitRec;
    assert(tube.hit({{0, 0, 0}, {1, 1, 2}}, 1e-3, FLT_MAX, &hitRec));

    for (int i = 0; i < 100; ++i) {
        Vector3d ro((float) drand48(), (float) drand48(), (float) drand48());
        Vector3d rd((float) drand48(), (float) drand48(), (float) drand48());
        if (tube.hit({ro, rd}, 1e-3, FLT_MAX, &hitRec)) {
            assert(hitRec.material == &mat);
            Vector3d p = hitRec.p - c;
            assert(p[1] >= -h / 2 && p[1] <= h / 2);
            assert_float_equal(p[0] * p[0] + p[2] * p[2], r * r);
            assert_vector3d_equal(ro + rd.normalize() * hitRec.t, hitRec.p);
            assert_float_equal(hitRec.n.getLength(), 1);
            assert_float_equal(hitRec.n.dot(o), 0);
        }
    }

    o = Vector3d(2.1, 1.1, -3.2);
    tube = Tube(c, o, r, h, &mat);
    for (int i = 0; i < 200; ++i) {
        Vector3d ro((float) drand48(), (float) drand48(), (float) drand48());
        Vector3d rd((float) drand48(), (float) drand48(), (float) drand48());
        if (tube.hit({ro, rd}, 1e-3, FLT_MAX, &hitRec)) {
            assert(hitRec.material == &mat);
            float b = std::abs((hitRec.p - c).dot(o.normalize()));
            assert(b <= h / 2);
            float e = (hitRec.p - c).getLength();
            assert_float_equal(e * e - b * b, r * r);
            assert_vector3d_equal(ro + rd.normalize() * hitRec.t, hitRec.p);
            assert_float_equal(hitRec.n.getLength(), 1);
            assert_float_equal(hitRec.n.dot(o), 0);
        }
    }

    return 0;
}
