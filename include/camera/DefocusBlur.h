#ifndef SIMPLE_RAY_TRACER_DEFOCUSBLUR_H
#define SIMPLE_RAY_TRACER_DEFOCUSBLUR_H

#include "Perspective.h"

// add depth of field
class DefocusBlur: public Perspective {

private:

    float diskRadius;

public:

    DefocusBlur(const Vector3d &pos, const Vector3d & view, const Vector3d & up, float dist, float width, float height, float aperture);

    Ray getRay(float x, float y) override;

    ~DefocusBlur() override = default;

};

#endif //SIMPLE_RAY_TRACER_DEFOCUSBLUR_H
