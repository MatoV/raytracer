#pragma once
#include <vector>
#include "Math/CMath.h"
#include "Math/Matrix/Matrix4.h"
#include "Core/Material/Material.h"

namespace mtr {

	////template<int_or_float T>
	////class Matrix4;

	class Intersection;

	template<int_or_float T>
	class Ray;

	class Object {
	public:

		virtual ~Object() {};
		
		virtual std::vector<Intersection> Intersect(const Ray<float>& ray) = 0;

		virtual Vector<float> Normal(const Vector<float>& point) const = 0;

		/* Returns transformation matrix */
		const Matrix4<float> GetTransform() const;
		
		/* Returns inverse transformation matrix */
		const Matrix4<float> GetInvTransform() const;

		/* Sets the transformation matrix to a given value */
		void SetTransform(Matrix4<float> matrix);
		
		/* Returns object's material */
		Material GetMaterial() const;

		/* Sets the material of the object */
		void SetMaterial(Material mat);

	protected:

		Object();

		Matrix4<float> m_transform;
		Matrix4<float> m_inverseTransform;
		Material m_material;
	};

	

}