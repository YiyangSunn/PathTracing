#include <cmath>

#include "util/math/Vector3d.h"

Vector3d::Vector3d() {
    dims[0] = 0;
    dims[1] = 0;
    dims[2] = 0;
}

Vector3d::Vector3d(float x, float y, float z) {
    dims[0] = x;
    dims[1] = y;
    dims[2] = z;
}

float Vector3d::getLength() const {
    return sqrtf(dims[0] * dims[0] + dims[1] * dims[1] + dims[2] * dims[2]);
}

Vector3d Vector3d::getNormalized() const {
    Vector3d vec = *this;
    vec.normalize();
    return vec;
}

Vector3d & Vector3d::normalize() {
    float length = getLength();
    dims[0] /= length;
    dims[1] /= length;
    dims[2] /= length;
    return *this;
}

float Vector3d::dot(const Vector3d & vec) const {
    return dims[0] * vec[0] + dims[1] * vec[1] + dims[2] * vec[2];
}

Vector3d Vector3d::cross(const Vector3d & vec) const {
    float x1 = dims[0], y1 = dims[1], z1 = dims[2];
    float x2 = vec[0], y2 = vec[1], z2 = vec[2];
    return {y1 * z2 - y2 * z1, z1 * x2 - x1 * z2, x1 * y2 - x2 * y1};
}

float Vector3d::operator[](int index) const {
    return dims[index];
}

float &Vector3d::operator[](int index) {
    return dims[index];
}

Vector3d operator+(const Vector3d & vec) {
    return vec;
}

Vector3d operator-(const Vector3d & vec) {
    return {-vec[0], -vec[1], -vec[2]};
}

Vector3d operator+(const Vector3d & vec1, const Vector3d & vec2) {
    return {vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]};
}

Vector3d operator-(const Vector3d & vec1, const Vector3d & vec2) {
    return {vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]};
}

Vector3d operator*(const Vector3d & vec1, const Vector3d & vec2) {
    return {vec1[0] * vec2[0], vec1[1] * vec2[1], vec1[2] * vec2[2]};
}

Vector3d operator/(const Vector3d & vec1, const Vector3d & vec2) {
    return {vec1[0] / vec2[0], vec1[1] / vec2[1], vec1[2] / vec2[2]};
}

Vector3d operator+(const Vector3d & vec, float val) {
    return {vec[0] + val, vec[1] + val, vec[2] + val};
}

Vector3d operator+(float val, const Vector3d & vec) {
    return vec + val;
}

Vector3d operator-(const Vector3d & vec, float val) {
    return {vec[0] - val, vec[1] - val, vec[2] - val};
}

Vector3d operator-(float val, const Vector3d & vec) {
    return {val - vec[0], val - vec[1], val - vec[2]};
}

Vector3d operator*(const Vector3d & vec, float val) {
    return {vec[0] * val, vec[1] * val, vec[2] * val};
}

Vector3d operator*(float val, const Vector3d & vec) {
    return vec * val;
}

Vector3d operator/(const Vector3d & vec, float val) {
    return {vec[0] / val, vec[1] / val, vec[2] / val};
}

Vector3d operator/(float val, const Vector3d & vec) {
    return {val / vec[0], val / vec[1], val / vec[2]};
}

std::ostream & operator<<(std::ostream & out, const Vector3d & vec) {
    out << "Vector3d{x=" << vec[0] << ",y=" << vec[1] << ",z=" << vec[2] << "}";
    return out;
}
