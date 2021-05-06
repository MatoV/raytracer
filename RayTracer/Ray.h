#pragma once
#include "Vector.h"
#include "CMath.h"
#include <vector>
#include "Matrix4.h"
#include "RayCommon.h"
#include "Object.h"
#include "Intersection.h"

namespace mtr {


	template<int_or_float T>
	class Ray {
	public:

		Ray(Vector<T> origin, Vector<T> direction);

		friend Ray operator*(const Matrix4<T>& m, const Ray<T>& r) {
			Ray ray{ m * r.GetOrigin(), m * r.GetDirection() };
			return ray;
		}

		/* Returns ray's origin point */
		Vector<T> GetOrigin() const;

		/* Returns ray's direction vector */
		Vector<T> GetDirection() const;

		/* Returns point at the gvien distance t along the ray */
		static Vector<T> Position(Ray ray, T t);

		/* Returns a vector of intersections between this ray and an object*/
		std::vector<Intersection> Intersect(Object* shape);

	private:
		Vector<T> origin;
		Vector<T> direction;
	};
	    
	template<int_or_float T>
	Ray<T>::Ray(Vector<T> origin, Vector<T> direction) : origin{ origin }, direction{ direction } {
	/*	std::cout << origin.x << '\n';
		std::cout << origin.y << '\n';
		std::cout << origin.z << '\n';*/
	}

	template<int_or_float T>
	Vector<T> Ray<T>::GetOrigin() const {
		return origin;
	}

	template<int_or_float T>
	Vector<T> Ray<T>::GetDirection() const {
		return direction;
	}

	template<int_or_float T>
	Vector<T> Ray<T>::Position(Ray ray, T t) {
		return ray.origin + ray.direction * t;
	}

	template<int_or_float T>
	std::vector<Intersection> Ray<T>::Intersect(Object* shape) {
		_ASSERT(shape);
		// Transforming ray by inverse transformation matrix of the shape
		// This way we can always assume that object is at world origin
		*this = shape->GetInvTransform() * (*this);
		return shape->Intersect(*this);
	}

}

