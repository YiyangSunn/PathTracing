#include <cassert>
#include "material/Metal.h"
#include "../test_helper.h"

int main() {
    Vector3d albedo(0.5, 0.5, 0.5);
    float fuzzy = 0;
    Metal mat(albedo, fuzzy);
    assert_vector3d_equal(mat.getAlbedo(), albedo);
    assert_float_equal(mat.getFuzzy(), fuzzy);

    Vector3d p(1.5, 1.5, 1.5);
    for (int i = 0; i < 100; ++i) {
        Vector3d din = Vector3d((float) drand48(), (float) drand48(), (float) drand48()).normalize();
        Vector3d n = Vector3d((float) drand48(), (float) drand48(), (float) drand48()).normalize();
        if (din.dot(n) >= 0) {
            din = -din;
        }
        Vector3d dout;
        Vector3d attenuation;
        if (mat.scatter(din, p, n, &dout, &attenuation)) {
            assert(n.dot(dout) > 0);
            assert_vector3d_equal((dout - din).normalize(), n);
        }
    }

    fuzzy = 0.99;
    mat = Metal(albedo, fuzzy);
    for (int i = 0; i < 100; ++i) {
        Vector3d din = Vector3d((float) drand48(), (float) drand48(), (float) drand48()).normalize();
        Vector3d n = Vector3d((float) drand48(), (float) drand48(), (float) drand48()).normalize();
        Vector3d dout;
        Vector3d attenuation;
        if (mat.scatter(din, p, n, &dout, &attenuation)) {
            if (din.dot(n) >= 0) {
                assert(n.dot(-dout) >= 0);
            } else {
                assert(n.dot(dout) >= 0);
            }
        }
    }

    return 0;
}
