#ifndef SIMPLE_RAY_TRACER_PERSPECTIVECAMERA_H
#define SIMPLE_RAY_TRACER_PERSPECTIVECAMERA_H

#include "AbstractCamera.h"

class PerspectiveCamera: public AbstractCamera {

public:

    PerspectiveCamera(const Vector3f & pos, const Vector3f & tar, const Vector3f & up, float dist, float width, float height);

    // (x, y) means that you're sampling the point at (width * x, height * y) on the image plane
    Ray getRay(float x, float y) override;

    ~PerspectiveCamera() override = default;

};

#endif //SIMPLE_RAY_TRACER_PERSPECTIVECAMERA_H
