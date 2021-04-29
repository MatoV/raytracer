#include "Geometric.h"


namespace mtr {

	float Dot(const Vector& a, const Vector& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Vector Cross(const Vector& a, const Vector& b) {
		Vector vec{};
		vec.x = a.y * b.z - a.z * b.y;
		vec.y = a.z * b.x - a.x * b.z;
		vec.z = a.x * b.y - a.y * b.x;

		return vec;
	}

	Vector Normalize(const Vector& vec) {
		float s = vec.Size();
		Vector nVec{ vec.x / s, vec.y / s, vec.z / s };
		return nVec;
	}

}