#pragma once

#include <algorithm>
#include <vector>
#include <iostream>



namespace mtr {

	class Object;

	class Intersection {
	public:
		Intersection(float distance, Object* shape);

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