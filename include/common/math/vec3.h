#ifndef INCLUDE_COMMON_MATH_VEC3_H_
#define INCLUDE_COMMON_MATH_VEC3_H_
#include <string>

namespace cmakub::math {
    struct Vec3 {
        float x, y, z;
        Vec3();
        Vec3(const Vec3& vec);
        Vec3(float x, float y, float z);

        float mag();
        void normalize();

        Vec3 cross(const Vec3& vec) const;
        Vec3 operator /(float d) const;
        Vec3 operator *(float n) const;
        Vec3 operator +(const Vec3& vec) const;
        Vec3 operator -(const Vec3& vec) const;
        float operator *(const Vec3& vec) const; //dot product
        Vec3 operator -() const;
    };
}

std::ostream& operator <<(std::ostream &out, const cmakub::math::Vec3 &vec);

#endif /* INCLUDE_COMMON_MATH_VEC3_H_ */
