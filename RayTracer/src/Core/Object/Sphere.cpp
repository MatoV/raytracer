
#include "Core/Object/Sphere.h"
#include "Math/Matrix/MatrixCommon.h"
#include <algorithm>
#include <iostream>


namespace mtr {

	mtr::Sphere::Sphere() {
	}

	Sphere::Sphere(Material material) {
		m_material = material;
	}

	

	std::vector<Intersection> Sphere::Intersect(const Ray<float>& ray) {
		std::vector<Intersection> values;

		auto rayOrigin = ray.GetOrigin();
		auto rayDir = ray.GetDirection();

		// vector from sphere's center to ray's origin (sphere is always at 0,0,0)
		auto sphereToRay = rayOrigin - mtr::Point(0.f, 0.f, 0.f);
		
		// compute discriminant
		auto a = mtr::Dot(rayDir, rayDir);
		auto b = 2 * mtr::Dot(rayDir, sphereToRay);
		auto c = mtr::Dot(sphereToRay, sphereToRay) - 1.f;
		
		float discriminant = b * b - 4 * a * c;
		if (discriminant >= 0.f) {
				
			float  t1 = (-b - sqrt(discriminant)) / (2.f * a);
			float t2 = (-b + sqrt(discriminant)) / (2.f * a);
			values.push_back(Intersection{ t1, this });
			values.push_back(Intersection{ t2, this });
				
			std::sort(values.begin(), values.end());

		}

		return values;	
	}
	Vector<float> Sphere::Normal(const Vector<float>& point) const {
		// transform point to object space and compute normal
		const auto objectPoint = m_inverseTransform * point;
		auto objectNormal = objectPoint - Point(0.f, 0.f, 0.f);
		// now we transform normal to world space
		auto worldNormal = Transpose(m_inverseTransform) * objectNormal;
		worldNormal.SetW(0.f);
		return Normalize(worldNormal);
	}
}
