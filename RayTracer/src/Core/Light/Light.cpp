#include "Math/Vector/Vector.h"
#include "Core/Object/Object.h"
#include "Core/Light/Light.h"
#include "Core/Material/Material.h"
#include "Math/Geometric.h"

namespace mtr {

    Light::Light() {
    }

    Vector<float> mtr::Light::GetPosition() const {
        return m_position;
    }

    void Light::SetPosition(Vector<float> pos) {
        m_position = pos;
    }

    Vector<float> Light::GetIntensity() {
        return m_intensity;
    }

    void Light::SetIntensity(Vector<float> intensity) {
        m_intensity = intensity;
    }


	Vector<float> Lightning(Object* obj, Light* light, const Vector<float>& pos, const Vector<float>& eyev, const Vector<float>& normal, bool inShadow) {

		Material m = obj->GetMaterial();
		// object color with light intensity
		auto effectiveColor = m.Color() * light->GetIntensity();
		// direction to light source
		auto lightv = Normalize(light->GetPosition() - pos);
		// ambient component
		auto ambient = effectiveColor * m.Ambient();

		const auto lightDotNormal = Dot(lightv, normal);

		// if lightDotNormal is less than 0, light is behind the surface (no diffuse and specular contributions)
		// or point is in shadow (another object is between point and a light)
		if (lightDotNormal < 0.f || inShadow) {
			return ambient;
		}
		auto diffuse = effectiveColor * m.Diffuse() * lightDotNormal;

		const auto reflectv = Reflect(-lightv, normal);
		const auto reflectDotEye = Dot(reflectv, eyev);

		if (reflectDotEye <= 0.f) {
			return ambient + diffuse;
		}
		const auto n = std::pow(reflectDotEye, m.Shininess());
		auto specular = light->GetIntensity() * m.Specular() * n;

		return ambient + diffuse + specular;
	}

}
