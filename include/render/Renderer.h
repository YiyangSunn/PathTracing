#ifndef SIMPLE_RAY_TRACER_RENDERER_H
#define SIMPLE_RAY_TRACER_RENDERER_H

#include "util/image/ImageBuffer.h"
#include "camera/Camera.h"
#include "object/Hittable.h"

// top interface for all renderers
class Renderer {

public:

    // render the scene onto im; other necessary components should be specified
    // in the constructor of subclass
    virtual void render(Camera * camera, Hittable * scene, ImageBuffer * im) = 0;

    virtual ~Renderer() = default;

};

#endif //SIMPLE_RAY_TRACER_RENDERER_H
