#ifndef SIMPLE_RAY_TRACER_RENDERER_H
#define SIMPLE_RAY_TRACER_RENDERER_H

#include "camera/Camera.h"
#include "scene/Scene.h"
#include "util/ImageBuffer.h"

// interface
class Renderer {

public:

    virtual void render(Camera * camera, Scene * scene, ImageBuffer * im) = 0;

};

#endif //SIMPLE_RAY_TRACER_RENDERER_H
