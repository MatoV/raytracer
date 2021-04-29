#pragma once
#include <compare>

namespace mtr {

	class Vector {
	public:
		Vector(float x, float y, float z, float w = 0.f);

		Vector();

		/* Comparison operators */
		std::partial_ordering operator<=>(const Vector& r) const;
		//bool operator==(const Vector& r);
		friend bool operator==(const Vector& rhs, const Vector& lhs);
		bool operator!=(const Vector& r);
		/* Addition */
		Vector& operator+=(const Vector& r);
		friend Vector operator+(Vector l, const Vector& r);
		/* Subtraction */
		Vector& operator-=(const Vector& r);
		friend Vector operator-(Vector l, const Vector& r);
		/* Scalar multiplication */
		Vector& operator*=(float r);
		friend Vector operator*(Vector l, float r);
		friend Vector operator*(float l, Vector r);
		/* Hadamard products */
		Vector& operator*=(const  Vector& r);
		friend Vector operator*(Vector l, const Vector& r);
		/* Division */
		Vector& operator/=(float r);
		friend Vector operator/(Vector l, float r);
		/* Negation */
		Vector operator-();
		/* Access operator */
		float& operator[](size_t element);
		float operator[](size_t element) const;

		float W() const { return w; }
		void SetW(float w) { w = w; }

		/* Returns magnitude of a vector */
		float Size() const;

		/* Vector components */
		float x, y, z;

	private:

		/* w component of the vector class, 0 by default, 1 if vector represents a point */
		float w;
	};


	/* Returns vector as a point */
	Vector Point(float x, float y, float z);

}
