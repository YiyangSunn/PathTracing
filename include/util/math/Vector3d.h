#ifndef SIMPLE_RAY_TRACER_VECTOR3D_H
#define SIMPLE_RAY_TRACER_VECTOR3D_H

#include <ostream>

// 3-dimensional vector
class Vector3d {

private:

    float dims[3]{};

public:

    Vector3d();

    Vector3d(float x, float y, float z);

    // get the length of the vector
    float getLength() const;

    // get the normalized instance
    Vector3d getNormalized() const;

    // normalize in place
    Vector3d & normalize();

    // compute the dot product
    float dot(const Vector3d & vec) const;

    // compute the cross product
    Vector3d cross(const Vector3d & vec) const;

    // override operators
    float operator[](int index) const;

    float & operator[](int index);

};

Vector3d operator+(const Vector3d & vec);

// reverse the direction
Vector3d operator-(const Vector3d & vec);

// element-wise operations
Vector3d operator+(const Vector3d & vec1, const Vector3d & vec2);

Vector3d operator-(const Vector3d & vec1, const Vector3d & vec2);

Vector3d operator*(const Vector3d & vec, const Vector3d & vec2);

Vector3d operator/(const Vector3d & vec, const Vector3d & vec2);

Vector3d operator+(const Vector3d & vec, float val);

Vector3d operator+(float val, const Vector3d & vec);

Vector3d operator-(const Vector3d & vec, float val);

Vector3d operator-(float val, const Vector3d & vec);

Vector3d operator*(const Vector3d & vec, float val);

Vector3d operator*(float val, const Vector3d & vec);

Vector3d operator/(const Vector3d & vec, float val);

Vector3d operator/(float val, const Vector3d & vec);

// for debugging or logging
std::ostream & operator<<(std::ostream & out, const Vector3d & vec);

#endif //SIMPLE_RAY_TRACER_VECTOR3D_H
