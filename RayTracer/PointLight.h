#pragma once
#include "Light.h"

namespace mtr {


	class PointLight : public Light {
	public:

		PointLight(Vector<float> position, Vector<float> intensity);

		PointLight();


	private:
	
	};

}