#pragma once
#include <concepts>
#include <cmath>
#include <type_traits>

namespace mtr {

	/* Requires floating point or integral type */
	template<typename T>
	concept int_or_float = std::is_floating_point<T>::value || std::is_integral<T>::value;
	
	/* Compares two floating point or integral values for equality */
	template<int_or_float T>
	bool IsEqual(const T a, const T b, int maxUlps = 4) {
		
		// Make sure maxUlps is non-negative and small enough that the    
		// default NAN won't compare as equal to anything.    

		if (std::is_integral<T>::value)
			return a == b;

		if (std::signbit(double(a)) != std::signbit(double(b)))
			return false;

		int aInt = *(int*)&a;
		// Make aInt lexicographically ordered as a twos-complement int    
		if (aInt < 0)
			aInt = 0x80000000 - aInt;
		// Make bInt lexicographically ordered as a twos-complement int    
		int bInt = *(int*)&b;
		if (bInt < 0)
			bInt = 0x80000000 - bInt;
		int intDiff = abs(aInt - bInt);
		if (intDiff <= maxUlps)
			return true;
		return false;
	}


}