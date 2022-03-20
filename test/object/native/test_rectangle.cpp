#include <cassert>
#include <cfloat>
#include <cmath>
#include "util/math/Vector3d.h"
#include "material/Lambertian.h"
#include "object/native/Rectangle.h"
#include "../../test_helper.h"

int main() {
    Vector3d c(1.1, 1.2, 0);
    Vector3d a = Vector3d(3.2, 1.2, 0) - c;
    Vector3d b = Vector3d(1.1, 2.3, 0) - c;
    Lambertian mat({0.2, 0.2, 0.2});
    Rectangle rect(c, a, b, &mat);
    Box box = rect.getBoundingBox();

    assert_vector3d_equal(rect.getC(), c);
    assert_vector3d_equal(rect.getB(), b);
    assert_vector3d_equal(rect.getA(), a);

    HitRecord hitRec;
    for (int i = 0; i < 300; ++i) {
        Vector3d o((float) drand48(), (float) drand48(), 0.1f);
        float x = (float) drand48() * 0.8f + 0.05f;
        float y = 0.95f - x;
        Vector3d target = c + x * a + y * b;
        Vector3d d = (target - o).normalize();
        assert(rect.hit({o, d}, 1e-3, FLT_MAX, &hitRec));
        assert_vector3d_equal(hitRec.p, target);
        assert_float_equal(hitRec.n.getLength(), 1);
        assert_float_equal(hitRec.n.dot(a), 0);
        assert(hitRec.material == &mat);
        assert_vector3d_equal(o + hitRec.t * d, hitRec.p);
        assert(box.contain(target));
    }

    for (int i = 0; i < 300; ++i) {
        float x = (float) drand48() * 4.f;
        float y = sqrtf(16 - x * x);
        Vector3d center = (a + b) / 2 + c;
        Vector3d target(center[0] + x, center[1] + y, center[2]);
        Vector3d o((float) drand48(), (float) drand48(), 0.1f);
        assert(!rect.hit({o, target - o}, 1e-3, FLT_MAX, &hitRec));
    }

    return 0;
}
