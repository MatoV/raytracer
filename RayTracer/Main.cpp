#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>

#include "mtr.h"



using namespace mtr;

void DrawClock() {
	size_t sizeX = 256;
	size_t sizeY = 256;
	Canvas canvas{ sizeX,sizeY };
	Color color{ 1.0, 0, 0 };

	Vector twelve{ 0,0,1 };

	auto centerX = sizeX / 2;
	auto centerY = sizeY / 2;

	for (auto i = 1; i <= 12; ++i) {
		auto rm = Rotate(Axis::Y, i * (M_PI_2 * 1 / 3));
		Vector v = rm * twelve;
		canvas.WritePixel(centerX + v.x * 100, centerY + v.z * 100, color);
	}
	canvas.SaveToFile();
}

int main() {
	
	

	//std::cout << "---------------- A --------------- " << '\n';
	//for (int i = 0; i < m1.length; ++i) {
	//	for (int j = 0; j < m1.length; ++j) {
	//		std::cout << "M[" << i << "," << j << "]=" << m1(i, j) << " ";
	//	}
	//	std::cout << '\n';





	return 0;
		


}


