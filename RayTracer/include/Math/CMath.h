#pragma once
#include <concepts>
#include <cmath>
#include <type_traits>

namespace mtr {
	
	// USEFUL MATH CONSTANTS
	constexpr auto M_E = 2.71828182845904523536;   // e
	constexpr auto M_LOG2E = 1.44269504088896340736;   // log2(e)
	constexpr auto M_LOG10E = 0.434294481903251827651;  // log10(e)
	constexpr auto M_LN2 = 0.693147180559945309417;  // ln(2)
	constexpr auto M_LN10 = 2.30258509299404568402;  // ln(10)
	constexpr auto M_PI = 3.14159265358979323846;  // pi
	constexpr auto M_PI_2 = 1.57079632679489661923;   // pi/2
	constexpr auto M_PI_4 = 0.785398163397448309616;  // pi/4
	constexpr auto M_1_PI = 0.318309886183790671538; // 1/pi
	constexpr auto M_2_PI = 0.636619772367581343076;  // 2/pi
	constexpr auto M_2_SQRTPI = 1.12837916709551257390;  // 2/sqrt(pi)
	constexpr auto M_SQRT2 = 1.41421356237309504880; // sqrt(2)
	constexpr auto M_SQRT1_2 = 0.707106781186547524401; // 1/sqrt(2)
	constexpr auto EPSILON = 0.005;

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

		if (a == T(0) && b == T(0)) return true;

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

	template<int_or_float T>
	bool IsZero(T value) {
		return (abs(value) < 0.00001);
	}


}