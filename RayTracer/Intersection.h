#pragma once

#include <algorithm>
#include <vector>
#include "CMath.h"


namespace mtr {

	class Object;

	template<int_or_float T>
	class Vector;

	/* Intersection data */
	struct IData {
		float t;
		bool inside;
		Object* object = nullptr;
		Vector<float> point;
		Vector<float> eye;
		Vector<float> normal;

	};

	class Intersection {
	public:
		Intersection(float distance, Object* shape);
		Intersection() = default;

		bool operator==(const Intersection& rhs) const;
		bool operator<(Intersection const& rhs) const;
		bool operator>(Intersection const& rhs) const;

		float value;
		Object* object;
	};

	Intersection Hit(const std::vector<Intersection>& intersections);

	/* Returns a sorted vector of intersection from a given arguments */
	template<typename ...Args>
	std::vector<Intersection> Intersections(Args const&... args) {
		std::vector<Intersection> xs{ args... };
		std::sort(xs.begin(), xs.end());
		return xs;
	}


}