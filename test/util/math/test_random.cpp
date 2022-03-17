#include <cassert>
#include "util/math/Vector3d.h"
#include "util/math/Random.h"

int main() {
    int n = 200;
    Vector3d s(0, 0, 0);
    for (int i = 0; i < n; ++i) {
        Vector3d p = Random::randomInUnitSphere();
        s = s + p;
        assert(p.getLength() < 1.f);
    }
    assert((s / (float) n).getLength() < 1e-1);
    return 0;
}
