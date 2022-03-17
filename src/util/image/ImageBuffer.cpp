#include "util/image/ImageBuffer.h"

ImageBuffer::ImageBuffer(int width, int height) {
    this->width = width;
    this->height = height;
    buffer = new Vector3d [width * height];
}

int ImageBuffer::getWidth() const {
    return width;
}

int ImageBuffer::getHeight() const {
    return height;
}

const Vector3d * ImageBuffer::operator[](int index) const {
    if (index < 0 || index >= height) {
        return nullptr;
    }
    return buffer + index * width;
}

Vector3d * ImageBuffer::operator[](int index) {
    if (index < 0 || index >= height) {
        return nullptr;
    }
    return buffer + index * width;
}

ImageBuffer::~ImageBuffer() {
    delete buffer;
    buffer = nullptr;
}

std::ostream & operator<<(std::ostream & out, const ImageBuffer & im) {
    out << "ImageBuffer{width=" << im.getWidth() << ",height=" << im.getHeight() << "}";
    return out;
}
