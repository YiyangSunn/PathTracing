#include "util/image/ImageBuffer.h"

ImageBuffer::ImageBuffer(int width, int height) {
    this->width = width;
    this->height = height;
    buffer = new Vector3d [width * height];
}

ImageBuffer::ImageBuffer(const ImageBuffer & im) {
    this->width = im.width;
    this->height = im.height;
    this->buffer = new Vector3d [width * height];
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

const Vector3d * ImageBuffer::operator[](int index) const {
    if (index < 0 || index >= height) {
        throw std::out_of_range("index exceeds height");
    }
    return buffer + index * width;
}

Vector3d * ImageBuffer::operator[](int index) {
    if (index < 0 || index >= height) {
        throw std::out_of_range("index exceeds height");
    }
    return buffer + index * width;
}

ImageBuffer::~ImageBuffer() {
    if (buffer != nullptr) {
        delete buffer;
        buffer = nullptr;
    }
}

std::ostream & operator<<(std::ostream & out, const ImageBuffer & im) {
    out << "ImageBuffer{width=" << im.getWidth() << ",height=" << im.getHeight() << "}";
    return out;
}
