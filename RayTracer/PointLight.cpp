#include "Vector.h"
#include "PointLight.h"


namespace mtr {


	PointLight::PointLight(Vector<float> position, Vector<float> intensity) {
		m_position = position;
		m_intensity = intensity;

	}

	PointLight::PointLight() {

	}

}