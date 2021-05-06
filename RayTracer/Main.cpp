#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include "mtr.h"
#include "RayCommon.h"
#include "Sphere.h"
#include "PointLight.h"
//#include <vld.h>


using namespace mtr;



void DrawClock() {
	size_t sizeX = 256;
	size_t sizeY = 256;
	Canvas canvas{ sizeX,sizeY };
	Vector<float> color{ 1.0, 0, 0 };

	Vector<float> twelve{ 0,0,1 };

	auto centerX = sizeX / 2;
	auto centerY = sizeY / 2;

	for (auto i = 1; i <= 12; ++i) {
		auto rm = Rotate(Axis::Y, i * (M_PI_2 * 1 / 3));
		auto v = rm * twelve;
		canvas.WritePixel(centerX + v.x * 100, centerY + v.z * 100, color);
	}
	canvas.SaveToFile();
}

void DrawSphere() {

	Material m1{ Vector{0.2f,1.f,0.2f}, 0.1f, 0.9f, 0.9f, 200.f };
	Object* s = new Sphere(m1);
	//Object* s2 = new Sphere(m1);
	Light* l = new PointLight(Vector{ -10.f, 10.f, -10.f, 1.f }, Vector{ 1.f,1.f, 1.f });
	//Vector eye{ 0.f, float(M_SQRT2 / 2.f), -float(M_SQRT2 / 2.f) };
	//Vector normal{ 0.f, 0.f, -1.f };
	//Vector pos{ 0.f, 0.f, 0.f, 1.f };


	size_t sizeX = 300;
	size_t sizeY = 300;
	Canvas canvas{ sizeX,sizeY };

	float  wallZ = 10.f;
	float  wallSize = 10.f;
	float halfSize = wallSize / 2.f;
	float pixelSize = wallSize / sizeX;

	auto hColor = Vector{ 1.f, 0.2f, 0.2f };
	auto mColor = Vector{ 0.f, 0.f, 0.f };

	//s2->SetTransform(Translate(Vector{-0.5f, 0.f, 0.f}) * Scale(Vector{ 0.5f, 0.5f, 0.5f }));
	s->SetTransform(Scale(Vector{ 0.4f, .4f, .4f }));

	Vector o{ 0.f, 0.f, -5.f, 1.f };


	for (auto i = 0; i < sizeX; ++i) {
		float worldY = halfSize - i * pixelSize;
		for (auto j = 0; j < sizeY; ++j) {
			float worldX = -halfSize + j * pixelSize;
			auto pos = Point(worldX, worldY, wallZ);
			auto dir = Normalize(pos - o);
			Ray<float> r = Ray<float>(o, dir);

			auto xs = r.Intersect(s);
			auto hit = Hit(xs);
			//auto xs2 = r.Intersect(s2);
			//auto hit2 = Hit(xs2);
			if (hit.object) {
				auto point = Ray<float>::Position(r, hit.value);
				auto normal = s->Normal(point);
				auto eye = Normalize(-r.GetDirection());
				auto c = Lightning(hit.object, l, point, eye, normal);
				canvas.WritePixel(i, j, c);
			}
			/*else if (hit2.object) {
				auto point = r.Position(r, hit2.value);
				auto normal = s2->Normal(point);
				auto eye = -r.GetDirection();
				auto c = Lightning(hit2.object, l, point, eye, normal);
				canvas.WritePixel(i, j, c);
			}*/
			else {
				canvas.WritePixel(i, j);
			}
		}
	}
	canvas.SaveToFile();

	delete s;
	//delete s2;
	delete l;

}


int main() {

	
	DrawSphere();

	return 0;
		


}


