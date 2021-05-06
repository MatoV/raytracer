#pragma once
#include "CMath.h"

namespace mtr {

	template<int_or_float T>
	class Vector;

	class Object;

	class Light {
	public:

		virtual ~Light() {};

		virtual Vector<float> GetPosition() const;
		virtual void SetPosition(Vector<float> pos);

		virtual Vector<float> GetIntensity();
		virtual void SetIntensity(Vector<float> intensity);

	protected:

		Light();

		Vector<float> m_position{ 0.f,0.f,0.f };
		Vector<float> m_intensity{ 1.f,1.f,1.f };
	};


	Vector<float> Lightning(Object* obj, Light* light, const Vector<float>& pos, const Vector<float>& eyev, const Vector<float>& normal);
}

