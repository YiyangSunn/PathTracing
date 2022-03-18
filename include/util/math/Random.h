#ifndef SIMPLE_RAY_TRACER_RANDOM_H
#define SIMPLE_RAY_TRACER_RANDOM_H

#include "Vector3d.h"

// utility class to get some random behavior
class Random {

public:

    // sample a random point in unit sphere
    static Vector3d randomInUnitSphere();

    // sample a random point in unit circle, the z value is always set to 0
    static Vector3d randomInUnitDisk();

};

#endif //SIMPLE_RAY_TRACER_RANDOM_H
