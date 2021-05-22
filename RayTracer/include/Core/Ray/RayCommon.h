#pragma once

#include "Math/CMath.h"
#include "Math/Geometric.h"
#include "Ray.h"

namespace mtr {

	enum class IntersectionObject {
		Sphere,
		Cube,
		Czlinder,
		Triangle
	};


	///* Returns tuple of intersection points between sphere and a ray*/
	//template<int_or_float T>
	//std::pair<T, T> Intersect(const Sphere<T>& sphere, const Ray<T>& ray) {
	//	std::pair<T, T> res{ 0,0 };
	//	auto rayOrigin = ray.GetOrigin();
	//	auto rayDir = ray.GetDirection();
	//	auto sphereRadius = sphere.GetRadius();

	//	// vector from sphere's center to ray's origin
	//	auto sphereToRay = rayOrigin - mtr::Point(0.f,0.f,0.f);

	//	// compute discriminant
	//	auto a = mtr::Dot(rayDir, rayDir);
	//	auto b = 2 * mtr::Dot(rayDir, sphereToRay);
	//	auto c = mtr::Dot(sphereToRay, sphereToRay) - (sphereRadius* sphereRadius);

	//	T discriminant = b * b - 4 * a * c;
	//	if (discriminant >= T(0)) {
	//		res.first = (-b - sqrt(discriminant)) / (T(2) * a);
	//		res.second = (-b + sqrt(discriminant)) / (T(2) * a);
	//		if (res.first > res.second) {
	//			res.swap(res);
	//		}
	//	}

	//	return res;
	//}



}