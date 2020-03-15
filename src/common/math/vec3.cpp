#include <ostream>
#include <cmath>
#include "common/math/vec3.h"

namespace cmakub::math {
	Vec3::Vec3() : x{}, y{}, z{} {}
	Vec3::Vec3(const Vec3& vec) : x{vec.x}, y{vec.y}, z{vec.z} {}
	Vec3::Vec3(float x, float y, float z) : x{x}, y{y}, z{z} {}

	float Vec3::mag() {
		return std::sqrt(x*x + y*y + z*z);
	}

	void Vec3::normalize() {
		float m = mag();
		x/=m;
		y/=m;
		z/=m;
	}

	Vec3 Vec3::cross(const Vec3& vec) const {
		return Vec3(y*vec.z - z*vec.y,
					z*vec.x - x*vec.z,
					x*vec.y - y*vec.x);
	}

	Vec3 Vec3::operator /(float n) const {
		return Vec3(x/n, y/n, z/n);
	}

	Vec3 Vec3::operator *(float n) const {
		return Vec3(x*n, y*n, z*n);
	}

	Vec3 Vec3::operator +(const Vec3& vec) const {
		return Vec3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vec3 Vec3::operator -(const Vec3& vec) const {
		return Vec3(x - vec.x, y - vec.y, z - vec.z);
	}

	float Vec3::operator *(const Vec3& vec) const { //dot product
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vec3 Vec3::operator -() const {
		return Vec3(-x, -y, -z);
	}
}

std::ostream& operator <<(std::ostream &out, const cmakub::math::Vec3 &vec) {
	return out << "Vec3(x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ")";
}
