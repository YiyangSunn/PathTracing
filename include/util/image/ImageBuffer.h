#ifndef SIMPLE_RAY_TRACER_IMAGEBUFFER_H
#define SIMPLE_RAY_TRACER_IMAGEBUFFER_H

#include "util/math/Vector3d.h"

// in-memory buffer used to store an image
class ImageBuffer {

private:

    int width;

    int height;

    Vector3d * buffer;

public:

    ImageBuffer(int width, int height);

    int getWidth() const;

    int getHeight() const;

    // get the ith row, start from zero
    const Vector3d * operator[](int index) const;

    Vector3d * operator[](int index);

    virtual ~ImageBuffer();

};

std::ostream & operator<<(std::ostream & out, const ImageBuffer & im);

#endif //SIMPLE_RAY_TRACER_IMAGEBUFFER_H
