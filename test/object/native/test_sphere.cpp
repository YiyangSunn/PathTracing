#include <cassert>
#include <cfloat>
#include "object/Hittable.h"
#include "object/native/Sphere.h"
#include "material/Lambertian.h"
#include "test_helper.h"

int main() {
    Vector3d center(0, 0, 0);
    float radius = 2.f;
    Material * mat = new Lambertian({0.3, 0.5, 0.7});
    Hittable * sphere = new Sphere(center, radius, mat);

    assert_box_equal(sphere->getBoundingBox(), {-radius, -radius, -radius, radius, radius, radius});

    for (int i = 0; i < 200; ++i) {
        Vector3d o = {(float) drand48() * 10.f, (float) drand48() * 10.f, (float) drand48() * 10.f};
        Vector3d d = Vector3d((float) drand48(), (float) drand48(), (float) drand48()).normalize();
        HitRecord hitRec;
        if (sphere->hit({o, d}, 1e-3, FLT_MAX, &hitRec)) {
            assert(hitRec.material == mat);
            assert_float_equal((hitRec.p - center).getLength(), radius);
            assert_float_equal((o + hitRec.t * d).getLength(), radius);
            assert_float_equal(hitRec.n.getLength(), 1.f);
            if (!sphere->hit({ o, -d}, 1e-3, FLT_MAX, &hitRec)) {
                assert(o.getLength() >= radius - 0.001f);
            } else {
                assert(o.getLength() <= radius + 0.001f);
            };
        }
    }

    delete sphere;
    delete mat;
    return 0;
}
