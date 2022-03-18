#ifndef SIMPLE_RAY_TRACER_PERSPECTIVE_H
#define SIMPLE_RAY_TRACER_PERSPECTIVE_H

#include "Camera.h"

class Perspective: public Camera {

protected:

    // position of the camera, or view point
    Vector3d e;

    // the direction along width
    Vector3d u;

    // the direction along height
    Vector3d v;

    // w points to -view
    Vector3d w;

    // distance between view point and the image plane
    float d;

    // width of the image plane
    float width;

    // height of the image plane
    float height;

public:

    Perspective(const Vector3d &pos, const Vector3d & view, const Vector3d & up, float dist, float width, float height);

    // (x, y) means that you're sampling the point at (width * x, height * y) on the image plane
    Ray getRay(float x, float y) override;

    ~Perspective() override = default;

};

#endif //SIMPLE_RAY_TRACER_PERSPECTIVE_H
