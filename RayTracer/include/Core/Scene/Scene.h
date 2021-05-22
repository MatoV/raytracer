#pragma once
#include <memory>
#include <vector>
#include "Core/Object/Object.h"
#include "Core/Light/Light.h"


namespace mtr {

	class Intersection;
	struct IData;

	using ObjectPtr = std::unique_ptr<Object>;
	using LightPtr = std::unique_ptr<Light>;


	class Scene {

	public:
		Scene();

		/* Returns all objects in the scene */
		const std::vector<ObjectPtr>& Objects() const { return m_objects; };

		/* Returns all lights in the scene */
		const std::vector<LightPtr>& Lights() const { return m_lights; };

		/* Adds a new light to the scene */
		void Add(LightPtr&& light) { m_lights.push_back(std::move(light)); };
		
		/* Adds a new object to the scene */
		void Add(ObjectPtr&& object) { m_objects.push_back(std::move(object)); };

	private:
		std::vector<LightPtr> m_lights;
		std::vector<ObjectPtr> m_objects;
	};

	/* Returns intersections of all objects in the scene */
	std::vector<Intersection> Intersect(const Scene& scene, Ray<float>& ray);

	Vector<float> ShadeHit(const Scene& scene, IData& intersectionData);

	/* Returns color of a hit object (returns black if nohing was hit */
	Vector<float> ColorAt(const Scene& scene, Ray<float>& ray);

	/* Returns true if point is in shadow */
	bool IsShadowed(const Scene& scene, Vector<float>& point);


}
