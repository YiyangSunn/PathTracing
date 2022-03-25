#include <cassert>
#include <cmath>
#include "material/Dielectric.h"
#include "test_helper.h"

int main() {
    float rfInside = 1.7;
    float rfOutside = 1.2;
    Vector3d albedo(1.2, 1.2, 1.2);
    Dielectric mat(rfInside, albedo, rfOutside);
    assert_vector3d_equal(mat.getAlbedo(), albedo);
    assert_float_equal(mat.getRefIdxInside(), rfInside);
    assert_float_equal(mat.getRefIdxOutside(), rfOutside);

    // enter from outside
    Vector3d n(-1.3, -2.1, 0);
    n.normalize();
    for (int i = 0; i < 200; ++i) {
        Vector3d din((float) drand48(), (float) drand48(), 0);
        din.normalize();
        Vector3d p(1.1, 1.2, 1.3);
        Vector3d dout;
        Vector3d attenuation;
        assert(mat.scatter(din, p, n, &dout, &attenuation));
        if (dout.dot(n) >= 0) {
            // should be reflection
            assert_vector3d_equal((dout - din).normalize(), n);
        } else {
            // should be refraction
            float cos1 = -n.dot(din);
            float cos2 = -n.dot(dout);
            assert(cos2 >= 0);
            float sin1 = sqrtf(1 - cos1 * cos1);
            float sin2 = sqrtf(1 - cos2 * cos2);
            assert_float_equal(rfOutside * sin1, rfInside * sin2);
        }
    }

    // enter from inside
    float sin0 = rfOutside / rfInside;
    for (int i = 0; i < 300; ++i) {
        Vector3d din(-(float) drand48(), -(float) drand48(), 0);
        din.normalize();
        Vector3d p(1.1, 1.2, 1.3);
        Vector3d dout;
        Vector3d attenuation;
        assert(mat.scatter(din, p, n, &dout, &attenuation));

        float cos1 = n.dot(din);
        float cos2 = n.dot(dout);
        float sin1 = sqrtf(1 - cos1 * cos1);
        float sin2 = sqrtf(1 - cos2 * cos2);

        if (sin1 >= sin0) {
            // should be total internal reflection
            assert(dout.dot(-n) >= 0);
            assert_vector3d_equal((dout - din).normalize(), -n);
        } else {
            if (dout.dot(-n) >= 0) {
                // should be reflection
                assert_vector3d_equal((dout - din).normalize(), -n);
            } else {
                // should be refraction
                assert(cos2 >= 0);
                assert_float_equal(rfInside * sin1, rfOutside * sin2);
            }
        }
    }
    return 0;
}
