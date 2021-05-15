#pragma once

#include "MatrixCommon.h"
#include "Vector.h"
#include "CMath.h"


namespace mtr {

	enum class Axis {
		X, Y, Z
	};

	template<int_or_float T = float>
	Matrix4<T> Translate(const Vector<T>& v) {
		Matrix4<T> m{ T(1) };

		m(0, 3) = v.x;
		m(1, 3) = v.y;
		m(2, 3) = v.z;

		return m;
	}

	template<int_or_float T = float>
	Matrix4<T> Scale(const Vector<T>& v) {
		Matrix4<T> m{ 1 };

		m(0, 0) = v.x;
		m(1, 1) = v.y;
		m(2, 2) = v.z;

		return m;
	}

	template<int_or_float T = float>
	Matrix4<T> Rotate(Axis axis, float angle) {
		Matrix4<T> rotation;

		float cosVal = cos(angle);
		float sinVal = sin(angle);
		//if (std::abs(cosVal) < 0.000001f) cosVal = 0.f;
		//if (std::abs(sinVal) < 0.000001f) sinVal = 0.f;
		cosVal = IsZero(cosVal) ? 0.f : cosVal;
		sinVal = IsZero(sinVal) ? 0.f : sinVal;
		switch (axis) {
			case Axis::X: 
			{
				T rotX[16] = { 1,0,0,0,0,cosVal,-sinVal,0,0,sinVal,cosVal,0,0,0,0,1 };
				rotation = Matrix4<T>{ rotX };
				break;
			}
			case Axis::Y:
			{
				T rotY[16] = { cosVal,0,sinVal,0,0,1,0,0,-sinVal,0,cosVal,0,0,0,0,1 };
				rotation = Matrix4<T>{ rotY };
				break;
			}
			case Axis::Z:
			{
				T rotZ[16] = { cosVal,-sinVal,0,0,sinVal,cosVal,0,0,0,0,1,0,0,0,0,1 };
				rotation = Matrix4<T>{ rotZ };
				break;
			}
			default:
				rotation = Matrix4<T>{ static_cast<T>(0) };
		}
		return rotation;
	}

	template<int_or_float T = float>
	Matrix4<T> ShearX(T y, T z) {
		T shear[16] = { 1,y,z,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		return Matrix4<T>{shear};
	}
	template<int_or_float T = float>
	Matrix4<T> ShearY(T x, T z) {
		T shear[16] = { 1,0,0,0,x,1,z,0,0,0,1,0,0,0,0,1 };
		return Matrix4<T>{shear};
	}
	template<int_or_float T = float>
	Matrix4<T> ShearZ(T x, T y) {
		T shear[16] = { 1,0,0,0,0,1,0,0,x,y,1,0,0,0,0,1 };
		return Matrix4<T>{shear};
	}

	template<int_or_float T>
	Matrix4<T> ViewTransform(const Vector<T>& from, const Vector<T>& to, const Vector<T>& up) {
		auto upN = Normalize(up);
		auto forward = Normalize(to - from);
		auto left = Cross(forward, upN);
		auto tUp = Cross(left, forward);

		T elements[16] = {left.x, left.y, left.z, T(0), tUp.x, tUp.y, tUp.z, T(0), -forward.x, -forward.y, -forward.z, T(0),T(0), T(0), T(0) , T(1)};
		auto orientation = Matrix4<T>{ elements };

		return orientation * Translate(Vector{ -from.x, -from.y, -from.z });
	}
}
