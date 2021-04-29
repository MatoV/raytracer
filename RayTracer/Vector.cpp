#include "Vector.h"
#include <algorithm>
#include <stdexcept>
#include "CMath.h"

namespace mtr {

	Vector::Vector(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
		if (w > 1.f) this->w = 0;

	}

	Vector::Vector() : Vector(0.f, 0.f, 0.f, 0.f) {
	}

	std::partial_ordering Vector::operator<=>(const Vector& r) const {
		return this->Size() <=> r.Size();
	}

	//bool Vector::operator==(const Vector& r) {
	//	if (IsEqual(x, r.x)
	//		&& IsEqual(y, r.y)
	//		&& IsEqual(z, r.z)
	//		&& IsEqual(w, r.w)) {
	//		return true;
	//	}
	//	return false;
	//}

	bool operator==(const Vector& rhs, const Vector& lhs) {
		if (IsEqual(lhs.x, rhs.x)
			&& IsEqual(lhs.y, rhs.y)
			&& IsEqual(lhs.z, rhs.z)
			&& IsEqual(lhs.w, rhs.w)) {
			return true;
		}
		return false;
	}

	bool Vector::operator!=(const Vector& r) {
		return !(*this == r);
	}

	Vector& Vector::operator+=(const Vector& r) {
		this->x += r.x; 
		this->y += r.y;
		this->z += r.z;
		this->w = std::clamp(w + r.w, 0.f,  1.f);
		return *this;
	}

	Vector& Vector::operator-=(const Vector& r) {
		this->x -= r.x;
		this->y -= r.y;
		this->z -= r.z;
		this->w = std::clamp(w - r.w, 0.f, 1.f);
		
		return *this;
	}

	Vector Vector::operator-() {
		*this = Vector(0, 0, 0) - *this;
		return *this;
	}

	float& Vector::operator[](size_t element) {
		if (element >= 4 || element < 0)
			throw std::out_of_range("Vector index out of bounds.");
		switch (element) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default: return x;
		}
	}
	
	float Vector::operator[](size_t element) const {
		if (element >= 4 || element < 0)
			throw std::out_of_range("Vector index out of bounds.");
		switch (element) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default: return x;
		}
	}

	float Vector::Size() const {
		return sqrtf(x * x + y * y + z * z);
	}

	Vector operator+(Vector l, const Vector& r) {
		l += r;
		return l;
	}

	Vector operator-(Vector l, const Vector& r) {
		l -= r;
		return l;
	}

	Vector& Vector::operator*=(float r) {
		this->x *= r;
		this->y *= r;
		this->z *= r;
		return *this;
	}

	Vector operator*(Vector l, float r) {
		l *= r;
		return l;
	}

	Vector operator*(float l, Vector r) {
		return r * l;
	}

	Vector operator*(Vector l, const Vector& r) {
		l *= r;
		return l;
	}

	Vector& Vector::operator*=(const Vector& r) {
		this->x = this->x * r.x;
		this->y = this->y * r.y;
		this->z = this->z * r.z;
		return *this;
	}

	Vector& Vector::operator/=(float r) {
		this->x *= 1/r;
		this->y *= 1/r;
		this->z *= 1/r;
		return *this;
	}

	Vector operator/(Vector l, float r) {
		l /= r;
		return l;;
	}

	Vector Point(float x, float y, float z) {
		return Vector(x, y, z, 1.f);
	}



}
