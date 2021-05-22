
#include "Core/Scene/Scene.h"
#include "Core/Light/PointLight.h"
#include "Core/Object/Sphere.h"
#include "Math/Matrix/MatrixTransform.h"
#include "Core/Intersection.h"
#include <iterator>

namespace mtr {

	Scene::Scene() {

		m_lights.push_back(std::make_unique<PointLight>(Point(-10.f, 10.f, -10.f), Vector{ 1.f, 1.f, 1.f }));

		//Material m{ Vector{0.8f, 1.f, 0.6f}, 0.1f, 0.7f, 0.2f };
		//Material m2{ Vector{0.8f, 1.f, 0.6f}, 0.1f, 0.7f, 0.4f };
		//auto s = std::make_unique<Sphere>(m);
		//auto s2 = std::make_unique<Sphere>(m2);
		//s2.get()->SetTransform(Translate(Vector{ -11.5f, 0.f, 0.f }));
		//m_objects.push_back(std::move(s));
		//m_objects.push_back(std::move(s2));


	}

	std::vector<Intersection> mtr::Intersect(const Scene& scene, Ray<float>& ray) {
		auto& objects = scene.Objects();
		auto& lights = scene.Lights();

		std::vector<Intersection> xs;
		xs.reserve(objects.size() * 2);

		// check intersections for every object
		std::for_each(objects.begin(), objects.end(), [&](auto& o) {
			auto is = ray.Intersect(o.get());
			//std::cout << o.get()->GetMaterial().Specular();
			xs.insert(
				xs.end(),
				std::make_move_iterator(is.begin()),
				std::make_move_iterator(is.end())
			);
			});

		std::sort(xs.begin(), xs.end());

		return xs;
	}

	Vector<float> ShadeHit(const Scene& scene, IData& id) {
		return Lightning(id.object, scene.Lights().at(0).get(), id.point, id.eye, id.normal, IsShadowed(scene, id.overPoint));
	}

	Vector<float> ColorAt(const Scene& scene, Ray<float>& ray) {
		auto xs = Intersect(scene, ray);
		auto hit = Hit(xs);

		if (hit.object) {
			auto id = ray.Precompute(hit);
			return ShadeHit(scene, id);
		}
		return Vector<float>{};
	}

	bool IsShadowed(const Scene& scene, Vector<float>& point) {
		Light* l = scene.Lights().at(0).get();

		auto pointToLight = l->GetPosition() - point;
		float dist = pointToLight.Size();
		auto dir = Normalize(pointToLight);

		Ray ray{ point, dir };

		auto xs = Intersect(scene, ray);
		auto hit = Hit(xs);

		if (hit.object && (hit.value < dist)) {
			return true;
		}

		return false;
	}

}
