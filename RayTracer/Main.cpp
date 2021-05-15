#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include "mtr.h"
#include "Scene.h"
#include "RayCommon.h"
#include "Sphere.h"
#include "PointLight.h"
#include "Camera.h"
//#include <vld.h>


using namespace mtr;




void DrawClock() {
	int sizeX = 256;
	int sizeY = 256;
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


	int sizeX = 350;
	int sizeY = 350;
	Canvas canvas{ sizeX,sizeY };

	float  wallZ = 10.f;
	float  wallSize = 10.f;
	float halfSize = wallSize / 2.f;
	float pixelSize = wallSize / sizeX;

	auto hColor = Vector{ 1.f, 0.2f, 0.2f };
	auto mColor = Vector{ 0.f, 0.f, 0.f };

	//s2->SetTransform(Translate(Vector{-0.5f, 0.f, 0.f}) * Scale(Vector{ 0.5f, 0.5f, 0.5f }));
	s->SetTransform(Scale(Vector{1.3f, 1.3f, 1.3f }));

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
void DrawScene() {
	Scene scene{};

	//Vector eye{ 0.f, float(M_SQRT2 / 2.f), -float(M_SQRT2 / 2.f) };
	//Vector normal{ 0.f, 0.f, -1.f };
	//Vector pos{ 0.f, 0.f, 0.f, 1.f };

	int sizeX = 350;
	int sizeY = 350;
	Canvas canvas{ sizeX,sizeY };

	float  wallZ = 10.f;
	float  wallSize = 10.f;
	float halfSize = wallSize / 2.f;
	float pixelSize = wallSize / sizeX;

	auto hColor = Vector{ 1.f, 0.2f, 0.2f };
	auto mColor = Vector{ 0.f, 0.f, 0.f };

	//s2->SetTransform(Translate(Vector{-0.5f, 0.f, 0.f}) * Scale(Vector{ 0.5f, 0.5f, 0.5f }));

	Vector o{ 0.f, 0.f, -5.f, 1.f };


	for (auto i = 0; i < sizeX; ++i) {
		float worldY = halfSize - i * pixelSize;
		for (auto j = 0; j < sizeY; ++j) {
			float worldX = -halfSize + j * pixelSize;
			auto pos = Point(worldX, worldY, wallZ);
			auto dir = Normalize(pos - o);
			Ray<float> r = Ray<float>(o, dir);

			//auto xs = r.Intersect(s);
			//auto hit = Hit(xs);
			////auto xs2 = r.Intersect(s2);
			////auto hit2 = Hit(xs2);
			//if (hit.object) {
			//	auto point = Ray<float>::Position(r, hit.value);
			//	auto normal = s->Normal(point);
			//	auto eye = Normalize(-r.GetDirection());
			//	auto c = Lightning(hit.object, l, point, eye, normal);
			//	canvas.WritePixel(i, j, c);
			//}
			/*else if (hit2.object) {
				auto point = r.Position(r, hit2.value);
				auto normal = s2->Normal(point);
				auto eye = -r.GetDirection();
				auto c = Lightning(hit2.object, l, point, eye, normal);
				canvas.WritePixel(i, j, c);
			}*/
			canvas.WritePixel(i, j, ColorAt(scene, r));
		}
	}
	canvas.SaveToFile();



}

void DrawChapter7() {

	Material floorMat{};
	floorMat.SetColor(Vector{ 1.f, 0.9f, 0.9f });
	floorMat.SetSpecular(0.f);
	ObjectPtr floorSphere = std::make_unique<Sphere>();
	floorSphere->SetTransform(Scale(Vector{ 10.f, 0.01f, 10.f }));
	floorSphere->SetMaterial(floorMat);

	ObjectPtr wallLeft = std::make_unique<Sphere>();
	wallLeft->SetTransform(Translate(Vector{ 0.f, 0.f, 5.f }) * Rotate(Axis::Y, -M_PI_4) * Rotate(Axis::X, M_PI_2) * Scale(Vector{ 10.f, 0.01f, 10.f }));
	wallLeft->SetMaterial(floorMat);

	ObjectPtr wallRight = std::make_unique<Sphere>();
	wallRight->SetTransform(Translate(Vector{ 0.f, 0.f, 5.f }) * Rotate(Axis::Y, M_PI_4) * Rotate(Axis::X, M_PI_2) * Scale(Vector{ 10.f, 0.01f, 10.f }));
	wallRight->SetMaterial(floorMat);

	Material sphereMat{};
	sphereMat.SetColor(Vector{ 0.745f, 0.274f, 0.274f });
	sphereMat.SetSpecular(0.3f);
	sphereMat.SetDiffuse(0.7f);
	ObjectPtr sphereMiddle = std::make_unique<Sphere>();
	sphereMiddle.get()->SetTransform(Translate(Vector{ -0.5f, 1.f, 0.5f }));
	sphereMiddle.get()->SetMaterial(sphereMat);

	sphereMat.SetColor(Vector{ 0.180f, 0.470f, 0.8f });
	sphereMat.SetSpecular(0.3f);
	sphereMat.SetDiffuse(0.7f);
	ObjectPtr sphereRight = std::make_unique<Sphere>();
	sphereRight.get()->SetTransform(Translate(Vector{ 1.5f, 0.5f, -0.5f }) * Scale(Vector{ 0.5f, 0.5f, 0.5f }));
	sphereRight.get()->SetMaterial(sphereMat);

	sphereMat.SetColor(Vector{ 0.184f, 0.537f, 0.254f });
	sphereMat.SetSpecular(0.3f);
	sphereMat.SetDiffuse(0.7f);

	auto sphereLeft = std::make_unique<Sphere>();
	sphereLeft->SetTransform(Translate(Vector{ -1.5f, 0.33f, -0.75f }) * Scale(Vector{ 0.33f, 0.33f, 0.33f }));
	sphereLeft->SetMaterial(sphereMat);

	Scene scene{};

	scene.Add(std::move(sphereLeft));
	scene.Add(std::move(sphereRight));
	scene.Add(std::move(floorSphere));
	scene.Add(std::move(sphereMiddle));
	scene.Add(std::move(wallLeft));
	scene.Add(std::move(wallRight));

	Camera cam{ 840, 420, M_PI / 3.f };
	cam.SetTransform(ViewTransform(Point(0.f, 1.5f, -7.f), Point(0.f, 1.f, 0.f), Vector{ 0.f, 1.f, 0.f }));

	auto canvas = cam.Render(scene);

	canvas.SaveToFile();
}

int main() {
	

	DrawChapter7();

	//for (auto i = 0; i < t.length; ++i) {
	//	for (auto j = 0; j < t.length; ++j) {
	//		std::cout << t(i, j) << ' ';
	//	}
	//	std::cout << '\n';
	//}

	//std::for_each(xs.begin(), xs.end(), [](Intersection& i) {
	//	std::cout << i.value << '\n';
	//});
	return 0;
		


}


