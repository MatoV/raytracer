#pragma once
#include "Math/Vector/Vector.h"
#include "Math/CMath.h"
#include <vector>
#include "Math/Matrix/Matrix4.h"
#include "RayCommon.h"
#include "Math/Geometric.h"
#include "Core/Object/Object.h"
#include "Core/Intersection.h"

namespace mtr {

	template<int_or_float T>
	class Ray {
	public:

		Ray(Vector<T> origin, Vector<T> direction);

		friend Ray operator*(const Matrix4<T>& m, const Ray<T>& r) {
			return Ray { m * r.GetOrigin(), m * r.GetDirection() };
		}

		/* Returns ray's origin point */
		Vector<T> GetOrigin() const;

		/* Returns ray's direction vector */
		Vector<T> GetDirection() const;

		/* Returns point at the gvien distance t along the ray */
		static Vector<T> Position(Ray ray, T t);

		/* Returns a vector of intersections between this ray and an object*/
		std::vector<Intersection> Intersect(Object* shape);

		/* Returns intersection data */
		IData Precompute(Intersection& intersection) const;

	private:
		Vector<T> m_origin;
		Vector<T> m_direction;
	};
	    
	template<int_or_float T>
	Ray<T>::Ray(Vector<T> origin, Vector<T> direction) : m_origin{ origin }, m_direction{ direction } {

	}

	template<int_or_float T>
	Vector<T> Ray<T>::GetOrigin() const {
		return m_origin;
	}

	template<int_or_float T>
	Vector<T> Ray<T>::GetDirection() const {
		return m_direction;
	}

	template<int_or_float T>
	Vector<T> Ray<T>::Position(Ray ray, T t) {
		return ray.m_origin + ray.m_direction * t;
	}

	template<int_or_float T>
	std::vector<Intersection> Ray<T>::Intersect(Object* shape) {
		_ASSERT(shape);
		// Transforming ray by inverse transformation matrix of the shape
		// We assume that an object is at world origin
		return shape->Intersect(shape->GetInvTransform() * (*this));
	}

	template<int_or_float T>
	IData Ray<T>::Precompute(Intersection& intersection) const {
		IData id;

		id.t = intersection.value;
		id.object = intersection.object;
		id.point = Position(*this, id.t);

		id.eye = Normalize(m_direction*-1.f);

		id.normal = id.object->Normal(id.point);
		if (Dot(id.eye, id.normal) < 0) {
			id.normal = -id.normal;
			id.inside = true;
		}
		else {
			id.inside = false;
		}
		id.overPoint = id.point + id.normal * EPSILON;

		return id;
	}

}

