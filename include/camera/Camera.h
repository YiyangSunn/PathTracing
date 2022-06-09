#ifndef SIMPLE_RAY_TRACER_CAMERA_H
#define SIMPLE_RAY_TRACER_CAMERA_H

#include "util/Ray.h"

// interface for all camera objects
class Camera {

public:

    // get the ray pointing from the view point to the image plane
    virtual Ray getRay(float x, float y) = 0;

};

#endif //SIMPLE_RAY_TRACER_CAMERA_H
