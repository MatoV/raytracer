#include "Intersection.h"
#include "Object.h"


namespace mtr {

	Intersection::Intersection(float distance, Object* shape) : value{ distance }, object{ shape } {
	}

	bool Intersection::operator==(const Intersection& rhs) const {
		return (rhs.object == this->object) && IsEqual(rhs.value, this->value);
	}

	bool Intersection::operator<(Intersection const& rhs) const {
		return value < rhs.value;
	}

	bool Intersection::operator>(Intersection const& rhs) const {
		return this->value > rhs.value;
	}

	Intersection Hit(const std::vector<Intersection>& intersections) {
		for (auto& i : intersections) {
			if (i.value >= 0.f) {
				return i;
			}
		}
		return { 0.f, nullptr };

	}

}

