#ifndef SIMPLE_RAY_TRACER_IMAGEBUFFER_H
#define SIMPLE_RAY_TRACER_IMAGEBUFFER_H

#include "util/Vector3f.h"

// in-memory buffer used to store an image
class ImageBuffer {

private:

    int width;

    int height;

    Vector3f * buffer;

public:

    ImageBuffer(int width, int height);

    ImageBuffer(const ImageBuffer & im);

    int getWidth() const;

    int getHeight() const;

    // get the ith row, start from zero
    const Vector3f * operator[](int index) const;

    Vector3f * operator[](int index);

    ImageBuffer & operator=(const ImageBuffer & im) = delete;

    virtual ~ImageBuffer();

};

#endif //SIMPLE_RAY_TRACER_IMAGEBUFFER_H
