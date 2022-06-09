#include "util/ImageBuffer.h"

ImageBuffer::ImageBuffer(int width, int height) {
    this->width = width;
    this->height = height;
    buffer = new Vector3f [width * height];
}

ImageBuffer::ImageBuffer(const ImageBuffer & im) {
    this->width = im.width;
    this->height = im.height;
    this->buffer = new Vector3f [width * height];
    for (int i = 0; i < width * height; ++i) {
        this->buffer[i] = im.buffer[i];
    }
}

int ImageBuffer::getWidth() const {
    return width;
}

int ImageBuffer::getHeight() const {
    return height;
}

const Vector3f * ImageBuffer::operator[](int index) const {
    return buffer + index * width;
}

Vector3f * ImageBuffer::operator[](int index) {
    return buffer + index * width;
}

ImageBuffer::~ImageBuffer() {
    if (buffer != nullptr) {
        delete buffer;
        buffer = nullptr;
    }
}
