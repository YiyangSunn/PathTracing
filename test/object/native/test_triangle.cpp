#include <cassert>
#include <cfloat>
#include <iostream>
#include "object/native/Triangle.h"
#include "material/Lambertian.h"
#include "test_helper.h"

int main() {
    Vector3d p[3] = {{1.1,  0,   0},
                     {-2.2, 0,   0},
                     {0,    1.6, 0}};
    Lambertian mat({0.2, 0.2, 0.2});
    Triangle tri(p[0], p[1], p[2], &mat);
    Box box = tri.getBoundingBox();
    Vector3d a = p[2] - p[1], b = p[0] - p[1];

    HitRecord hitRec;
    for (int i = 0; i < 300; ++i) {
        float x = (float) drand48() * 0.8f + 0.05f;
        float y = 0.95f - x;
        Vector3d o((float) drand48(), (float) drand48(), (float) drand48() + 0.01f);
        Vector3d c = x * a + y * b + p[1];
        assert(tri.hit({o, c - o}, 1e-3, FLT_MAX, &hitRec));
        assert_vector3d_equal(hitRec.p, c);
        assert_float_equal(hitRec.n.getLength(), 1);
        assert_vector3d_equal(hitRec.n.cross({0, 0, 1}), {0, 0, 0});
        assert(hitRec.material == &mat);
        assert(box.contain(hitRec.p));
    }

    for (int i = 0; i < 300; ++i) {
        Vector3d o((float) drand48(), (float) drand48(), (float) drand48());
        Vector3d d = Vector3d((float) drand48(), (float) drand48(), (float) drand48()).normalize();
        if (tri.hit({o, d}, 1e-3, FLT_MAX, &hitRec)) {
            assert_float_equal(hitRec.n.getLength(), 1);
            assert_vector3d_equal(hitRec.n.cross({0, 0, 1}), {0, 0, 0});
            assert(hitRec.material == &mat);
            assert_vector3d_equal(o + hitRec.t * d, hitRec.p);
            Vector3d c = hitRec.p - p[1];
            float det = a[0] * b[1] - a[1] * b[0];
            float y = (c[1] * a[0] - c[0] * a[1]) / det;
            float x = (c[0] * b[1] - c[1] * b[0]) / det;
            assert(y > 0 && y < 1);
            assert(x > 0 && x < 1);
            assert(box.contain(hitRec.p));
        }
    }

    Vector3d u(-3, 2, 0);
    a = p[2] - u;
    b = p[1] - u;
    for (int i = 0; i < 300; ++i) {
        float x = (float) drand48() * 0.8f + 0.05f;
        float y = 0.95f - x;
        Vector3d o((float) drand48(), (float) drand48(), (float) drand48() + 0.01f);
        Vector3d c = x * a + y * b + u;
        assert(!tri.hit({o, c - o}, 1e-3, FLT_MAX, &hitRec));
    }

    u = Vector3d(3, 2, 0);
    a = p[2] - u;
    b = p[0] - u;
    for (int i = 0; i < 300; ++i) {
        float x = (float) drand48() * 0.8f + 0.05f;
        float y = 0.95f - x;
        Vector3d o((float) drand48(), (float) drand48(), (float) drand48() + 0.01f);
        Vector3d c = x * a + y * b + u;
        assert(!tri.hit({o, c - o}, 1e-3, FLT_MAX, &hitRec));
    }

    u = Vector3d(0, -2, 0);
    a = p[0] - u;
    b = p[1] - u;
    for (int i = 0; i < 300; ++i) {
        float x = (float) drand48() * 0.8f + 0.05f;
        float y = 0.95f - x;
        Vector3d o((float) drand48(), (float) drand48(), (float) drand48() + 0.01f);
        Vector3d c = x * a + y * b + u;
        assert(!tri.hit({o, c - o}, 1e-3, FLT_MAX, &hitRec));
    }

    return 0;
}
