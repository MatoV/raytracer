#include "Math/Vector/Vector.h"
#include "Core/Light/PointLight.h"


namespace mtr {


	PointLight::PointLight(Vector<float> position, Vector<float> intensity) {
		m_position = position;
		m_intensity = intensity;

	}

	PointLight::PointLight() {

	}

}