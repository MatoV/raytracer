#pragma once
#include "Math/Vector/Vector.h"
#include "CMath.h"

namespace mtr {


	/* Returns vector dot product (scalar product) */
	template<int_or_float T = float>
	T Dot(const Vector<T>& a, const Vector<T>& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/* Returns vector cross product */
	template<int_or_float T = float>
	Vector<T> Cross(const Vector<T>& a, const Vector<T>& b) {
		Vector<T> vec{};
		vec.x = a.y * b.z - a.z * b.y;
		vec.y = a.z * b.x - a.x * b.z;
		vec.z = a.x * b.y - a.y * b.x;

		return vec;
	}

	/* Creates normalized vector from a given vector( 0 < size < 1) */
	template<int_or_float T = float>
	Vector<T> Normalize(const Vector<T>& vec) {
		T s = vec.Size();
		Vector<T> nVec{ vec.x / s, vec.y / s, vec.z / s };
		return nVec;
	}

	/* For the incident vector I and surface orientation N, returns the reflection direction */
	template<int_or_float T = float>
	Vector<T> Reflect(const Vector<T>& i, const Vector<T>& n) {
		return i - 2.f * Dot(n, i) * n;
	}

}