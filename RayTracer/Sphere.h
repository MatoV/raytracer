#pragma once
#include "RayCommon.h"
#include "Object.h"
#include "Intersection.h"

namespace mtr {


class Sphere : public Object {
public:
	Sphere();

	Sphere(Material material);

	/* Returns vector of intersection points between sphere and a ray*/
	std::vector<Intersection> Intersect(const Ray<float>& ray) override;

	/* Returns normal vector of the object at a given point */
	Vector<float> Normal(const Vector<float>& worldPoint) const override;


};


//template<int_or_float T>
//Sphere<T>::Sphere() : Sphere(T(1)) {
//}
//
//template<int_or_float T>
//Sphere<T>::Sphere(T radius) : radius(radius) {
//}
//
//template<int_or_float T>
//std::vector<Intersection<T>> Sphere<T>::Intersect(const Ray<T>& ray) {
//	std::vector<Intersection<T>> values;
//	std::cout << "Size" << values.size() << '\n';
//	auto rayOrigin = ray.GetOrigin();
//	auto rayDir = ray.GetDirection();
//	auto sphereRadius = this->GetRadius();
//
//	// vector from sphere's center to ray's origin (sphere is always at 0,0,0)
//	auto sphereToRay = rayOrigin - mtr::Point(0.f, 0.f, 0.f);
//
//	// compute discriminant
//	auto a = mtr::Dot(rayDir, rayDir);
//	auto b = 2 * mtr::Dot(rayDir, sphereToRay);
//	auto c = mtr::Dot(sphereToRay, sphereToRay) - (sphereRadius * sphereRadius);
//
//	T discriminant = b * b - 4 * a * c;
//	if (discriminant >= T(0)) {
//		Intersection<T> i{}, j{};
//		i.value = (-b - sqrt(discriminant)) / (T(2) * a);
//		i.object = this;
//		j.value = (-b + sqrt(discriminant)) / (T(2) * a);
//		j.object = this;
//		values.push_back(i);
//		values.push_back(j);
//		
//		std::ranges::sort(values, [](const Intersection<T>& a, const Intersection<T>& b) {
//			return a.value < b.value; });
//	}
//	std::cout << "Size" << values.size() << '\n';
//
//	return values;
//}

}