#include "util/math/Random.h"

// we use a rejection method here
Vector3d Random::randomInUnitSphere() {
    float x = 0, y = 0, z = 0;
    do {
        // sample a random point in the 2 x 2 x 2 cube
        x = 2.f * ((float)drand48() - 0.5f);
        y = 2.f * ((float)drand48() - 0.5f);
        z = 2.f * ((float)drand48() - 0.5f);
    } while (x * x + y * y + z * z >= 0.99f);
    return {x, y, z};
}

Vector3d Random::randomInUnitDisk() {
    float x = 0, y = 0;
    do {
        // sample a random point in the 2 * 2 square
        x = 2.f * ((float) drand48() - 0.5f);
        y = 2.f * ((float) drand48() - 0.5f);
    } while (x * x + y * y >= 0.99f);
    return {x, y, 0};
}
