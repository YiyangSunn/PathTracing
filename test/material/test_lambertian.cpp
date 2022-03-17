#include <cassert>
#include "material/Lambertian.h"
#include "test_helper.h"

int main() {
    Vector3d albedo(0.3, 0.5, 0.7);
    Material * mat = new Lambertian(albedo);
    assert_vector3d_equal(mat->getAttenuation(), albedo);

    Vector3d s(0, 0, 0);
    Vector3d p(1, 1, 1);
    Vector3d n(0, 1, 0);
    Vector3d din(1, 1, 1);
    Vector3d dout(2, 2, 2);
    int m = 200;
    for (int i = 0; i < m; ++i) {
        assert(mat->scatter(din, p, n, &dout));
        s = s + dout;
    }
    assert((s.normalize() - n).getLength() < 1e-1);

    delete mat;

    return 0;
}
