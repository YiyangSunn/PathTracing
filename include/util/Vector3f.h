#ifndef SIMPLE_RAY_TRACER_VECTOR3F_H
#define SIMPLE_RAY_TRACER_VECTOR3F_H

#include <cmath>
#include <algorithm>

// 使用 float 的 3 维向量
class Vector3f {

private:

    float x;

    float y;

    float z;

public:

    inline Vector3f() {
        x = 0;
        y = 0;
        z = 0;
    }

    inline Vector3f(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // 获取向量长度
    inline float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // 获取单位向量
    inline Vector3f normalized() const {
        return *this / length();
    }

    // 原地归一化
    inline Vector3f & normalize() {
        return *this /= length();
    }

    // 向量点乘
    inline float dot(const Vector3f & v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // 向量叉乘
    inline Vector3f cross(const Vector3f & v) const {
        return {y * v.z - v.y * z, z * v.x - x * v.z, x * v.y - v.x * y};
    }

    // 获取各个分量
    inline float operator[](int idx) const {
        return (idx == 0) ? x : ((idx == 1) ? y : z);
    }

    inline float & operator[](int idx) {
        return (idx == 0) ? x : ((idx == 1) ? y : z);
    }

    // 一元运算
    friend inline Vector3f operator+(const Vector3f & v) {
        return v;
    }

    friend inline Vector3f operator-(const Vector3f & v) {
        return {-v.x, -v.y, -v.z};
    }

    // 四则运算
    friend inline Vector3f operator+(const Vector3f & v1, const Vector3f & v2) {
        return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    }

    friend inline Vector3f operator-(const Vector3f & v1, const Vector3f & v2) {
        return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
    }

    friend inline Vector3f operator*(const Vector3f & v1, const Vector3f & v2) {
        return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
    }

    friend inline Vector3f operator/(const Vector3f & v1, const Vector3f & v2) {
        return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
    }

    friend inline Vector3f operator+(const Vector3f & vec, float val) {
        return {vec.x + val, vec.y + val, vec.z + val};
    }

    friend inline Vector3f operator+(float val, const Vector3f & vec) {
        return {val + vec.x, val + vec.y, val + vec.z};
    }

    friend inline Vector3f operator-(const Vector3f & vec, float val) {
        return {vec.x - val, vec.y - val, vec.z - val};
    }

    friend inline Vector3f operator-(float val, const Vector3f & vec) {
        return {val - vec.x, val - vec.y, val - vec.z};
    }

    friend inline Vector3f operator*(const Vector3f & vec, float val) {
        return {vec.x * val, vec.y * val, vec.z * val};
    }

    friend inline Vector3f operator*(float val, const Vector3f & vec) {
        return {val * vec.x, val * vec.y, val * vec.z};
    }

    friend inline Vector3f operator/(const Vector3f & vec, float val) {
        return {vec.x / val, vec.y / val, vec.z / val};
    }

    friend inline Vector3f operator/(float val, const Vector3f & vec) {
        return {val / vec.x, val / vec.y, val / vec.z};
    }

    friend inline Vector3f & operator+=(Vector3f & v1, const Vector3f & v2) {
        v1.x += v2.x;
        v1.y += v2.y;
        v1.z += v2.z;
        return v1;
    }

    friend inline Vector3f & operator-=(Vector3f & v1, const Vector3f & v2) {
        v1.x -= v2.x;
        v1.y -= v2.y;
        v1.z -= v2.z;
        return v1;
    }

    friend inline Vector3f & operator*=(Vector3f & v1, const Vector3f & v2) {
        v1.x *= v2.x;
        v1.y *= v2.y;
        v1.z *= v2.z;
        return v1;
    }

    friend inline Vector3f & operator/=(Vector3f & v1, const Vector3f & v2) {
        v1.x /= v2.x;
        v1.y /= v2.y;
        v1.z /= v2.z;
        return v1;
    }

    friend inline Vector3f & operator+=(Vector3f & vec, float val) {
        vec.x += val;
        vec.y += val;
        vec.z += val;
        return vec;
    }

    friend inline Vector3f & operator-=(Vector3f & vec, float val) {
        vec.x -= val;
        vec.y -= val;
        vec.z -= val;
        return vec;
    }

    friend inline Vector3f & operator*=(Vector3f & vec, float val) {
        vec.x *= val;
        vec.y *= val;
        vec.z *= val;
        return vec;
    }

    friend inline Vector3f & operator/=(Vector3f & vec, float val) {
        vec.x /= val;
        vec.y /= val;
        vec.z /= val;
        return vec;
    }

    static inline Vector3f max(const Vector3f & v1, const Vector3f & v2) {
        return {std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z)};
    }

    static inline Vector3f min(const Vector3f & v1, const Vector3f & v2) {
        return {std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z)};
    }

};

#endif //SIMPLE_RAY_TRACER_VECTOR3F_H
