#include "Math/Vector/Vector.h"
#include "Core/Material/Material.h"

mtr::Material::Material() : Material(Vector{ 1.f, 1.f, 1.f }, 0.5f, 0.5f, 0.5f, 50.f) {
}

mtr::Material::Material(Vector<float> color, float ambient, float diffuse, float specular, float s) \
	: m_color{ color }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular }, m_shininess{ s } {
}

bool mtr::Material::operator==(const Material& rhs) {
	return IsEqual(m_ambient, rhs.m_ambient) && IsEqual(m_diffuse, rhs.m_diffuse)
		&& IsEqual(m_specular, rhs.m_specular) && IsEqual(m_shininess, rhs.m_shininess) && m_color == rhs.m_color;
}

void mtr::Material::SetAmbient(float a) {
	m_ambient = std::clamp(a, 0.f, 1.f);
}

void mtr::Material::SetDiffuse(float d) {
	m_diffuse = std::clamp(d, 0.f, 1.f);
}

void mtr::Material::SetSpecular(float s) {
	m_specular = std::clamp(s, 0.f, 1.f);
}

void mtr::Material::SetShininess(float s) {
	m_shininess = std::clamp(s, 0.f, 10000.f);
}

void mtr::Material::SetColor(Vector<float> c) {
	m_color = c;
}
