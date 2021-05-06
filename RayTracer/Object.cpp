#include "Object.h"
#include "MatrixCommon.h"
namespace mtr {

	Object::Object() : m_transform{ 1.f }, m_inverseTransform{ 1.f }, m_material{} {
	}

	void Object::SetTransform(Matrix4<float> matrix) {
		m_transform = matrix;
		m_inverseTransform = Inverse(matrix);
	}

	const Matrix4<float> Object::GetTransform() const {
		return m_transform;
	}

	const Matrix4<float> Object::GetInvTransform() const {
		return m_inverseTransform;
	}

	Material Object::GetMaterial() const {
		return m_material;
	}

	/* Sets the material of the object */
	void Object::SetMaterial(Material mat) {
		m_material = mat;
	}

}
