#ifndef SIMPLE_RAY_TRACER_ABSTRACT_CAMERA_H
#define SIMPLE_RAY_TRACER_ABSTRACT_CAMERA_H

#include "Camera.h"

class AbstractCamera: public Camera {

protected:

    // position of the camera, or view point
    Vector3f e;

    // the direction along width
    Vector3f u;

    // the direction along height
    Vector3f v;

    // w points to -view
    Vector3f w;

    // distance between view point and the image plane
    float d;

    // width of the image plane
    float width;

    // height of the image plane
    float height;

public:

    // view, up should be normalized
    AbstractCamera(const Vector3f & pos, const Vector3f & view, const Vector3f & up, float dist, float width, float height);

    virtual ~AbstractCamera() = default;

};

#endif //SIMPLE_RAY_TRACER_ABSTRACT_CAMERA_H
