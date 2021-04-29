#pragma once
#include "Vector.h"

namespace mtr {


	/* Returns vector dot product (scalar product) */
	float Dot(const Vector& a, const Vector& b);

	/* Returns vector cross product */
	Vector Cross(const Vector& a, const Vector& b);

	/* Creates normalized vector from a given vector( 0 < size < 1) */
	Vector Normalize(const Vector& vec);

}