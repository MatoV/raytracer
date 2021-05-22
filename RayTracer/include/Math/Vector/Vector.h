#pragma once
#include <compare>
#include <algorithm>
#include <stdexcept>
#include "Math/CMath.h"
#include <iostream>


namespace mtr {

	template<int_or_float T = float>
	class Vector {
	public:

		Vector();
		Vector(T x, T y, T z, T w = static_cast<T>(0));

		/* Comparison operators */
		std::partial_ordering operator<=>(const Vector<T>& r) const {
			return this->Size() <=> r.Size();
		}
		//bool operator==(const Vector& r);
		friend bool operator==(const Vector& rhs, const Vector<T>& lhs) {
			if (IsEqual(lhs.x, rhs.x)
				&& IsEqual(lhs.y, rhs.y)
				&& IsEqual(lhs.z, rhs.z)
				&& IsEqual(lhs.w, rhs.w)) {
				return true;
			}
			return false;
		}
		bool operator!=(const Vector<T>& r) {
			return !(*this == r);
		}
		/* Assignment */
		Vector<T>& operator=(const Vector<T>& other) {
			if (this == &other) return *this;
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			this->w = other.W();
			return *this;
		}

		/* Addition */
		Vector<T>& operator+=(const Vector<T>& r) {
			this->x += r.x;
			this->y += r.y;
			this->z += r.z;
			this->w = std::clamp(w + r.w, T(0), T(1));
			return *this;

		}
		friend Vector<T> operator+(Vector<T> l, const Vector<T>& r) {
			l += r;
			return l;
		}
		/* Subtraction */
		Vector& operator-=(const Vector<T>& r) {
			this->x -= r.x;
			this->y -= r.y;
			this->z -= r.z;
			this->w = std::clamp(w - r.w, T(0), T(1));

			return *this;
		}
		friend Vector<T> operator-(Vector<T> l, const Vector<T>& r) {
			l -= r;
			return l;
		}
		/* Scalar multiplication */
		Vector<T>& operator*=(T r) {
			this->x *= r;
			this->y *= r;
			this->z *= r;
			return *this;
		}
		friend Vector<T> operator*(Vector l, T r) {
			l *= r;
			return l;
		}
		friend Vector<T> operator*(T l, Vector<T> r) {
			return r * l;
		}
		/* Hadamard products */
		Vector<T>& operator*=(const  Vector<T>& r) {
			this->x = this->x * r.x;
			this->y = this->y * r.y;
			this->z = this->z * r.z;
			return *this;
		
		}
		friend Vector<T> operator*(Vector<T> l, const Vector<T>& r) {
			l *= r;
			return l;
		}
		/* Division */
		Vector<T>& operator/=(T r) {
			this->x *= 1 / r;
			this->y *= 1 / r;
			this->z *= 1 / r;
			return *this;
		}
		friend Vector<T> operator/(Vector<T> l, T r) {
			l /= r;
			return l;
		}
		/* Negation */
		Vector<T> operator-() {
			*this = Vector(T(0), T(0), T(0)) - *this;
			return *this;
		}
		/* Access operator */
		T& operator[](size_t element) {
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
		T operator[](size_t element) const {
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


		T W() const { return w; }
		void SetW(T w) { w = w; }

		/* Returns magnitude of a vector */
		T Size() const;

		/* Vector components */
		T x, y, z;

	private:
		/* w component of the vector class, 0 by default, 1 if vector represents a point */
		T w;
	};


	template<int_or_float T>
	Vector<T>::Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
		if (w > 1.f) this->w = T(0);

	}

	template<int_or_float T>
	Vector<T>::Vector() : Vector(T(0), T(0), T(0), T(0)) {
	}

	template<int_or_float T>
	T Vector<T>::Size() const {
		return std::sqrt(x * x + y * y + z * z);
	}


	/* Returns vector as a point */
	template<int_or_float T = float>
	Vector<T> Point(T x, T y, T z) {
		return Vector<T>(x, y, z, T(1));

	}



}
