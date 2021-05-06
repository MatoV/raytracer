#pragma once
#include "CMath.h"


namespace mtr {

	template<int_or_float T>
	class Vector;

	class Material {

	public:
		Material();
		Material(Vector<float> color,float ambient, float diffuse, float specular, float s = 50.f);

		bool operator==(const Material& rhs);

		float Ambient() const { return m_ambient; };
		float Diffuse() const { return m_diffuse; };
		float Specular() const { return m_specular; };
		float Shininess() const { return m_shininess; };
		Vector<float> Color() const { return m_color; };

		void SetAmbient(float a);
		void SetDiffuse(float d);
		void SetSpecular(float s);
		void SetShininess(float s);
		void SetColor(Vector<float> c);

	private:
		Vector<float> m_color;
		float m_ambient;
		float m_diffuse;
		float m_specular;
		float m_shininess;

	};

}