#include "Core/Canvas.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace mtr {



	Canvas::Canvas(int width, int height) : width(width), height(height) {
		pixels.resize(width*height);
		std::ranges::fill(pixels, mtr::Vector<float>(0.f, 0.f, 0.f));
	}

	void Canvas::WritePixel(int x, int y, mtr::Vector<float> color) {
		if (x >= width || x < 0 || y >= height || y < 0) {
			throw std::domain_error("Index out of range.");
		}
		pixels[y*width + x] = color;
	}

	mtr::Vector<float>& Canvas::PixelAt(int x, int y)  {
		if (x >= width || x < 0 || y >= height || y < 0) {
			throw std::domain_error("Index out of range.");
		}
		return pixels[y * width + x];
	}

	bool Canvas::SaveToFile()  {

		std::ofstream file{ "raytracedChapter7.ppm" };

		// Adding a header
		file << "P3\n" << width << " " << height << '\n' << "255\n";

		// Outputting colors (max line width is 70 chars)
		const size_t lineSize = 70;
		std::stringstream line{};

		for (auto i = 0; i < height; ++i) {
			for (auto j = 0; j < width; ++j) {
				mtr::Vector<float>  c = PixelAt(j, i);
				std::string s{};
				s.append(std::to_string(floatTo255RGB(c.x)));
				s.append(" ");
				s.append(std::to_string(floatTo255RGB(c.y)));
				s.append(" ");
				s.append(std::to_string(floatTo255RGB(c.z)));
				auto size = line.str().size();
				if (size + s.size() > lineSize) {
					line << "\n";
					file << line.str();
					line.str("");
					line.clear();
				}
				line << s << " ";
			}
			file << line.str();
			file << '\n';
			line.str("");
			line.clear();
		}
		
		file << '\n';
		file.close();

		return true;

	}

	int Canvas::floatTo255RGB(float c) {
		int n = std::clamp(static_cast<int>(c * 255), 0, 255);
		return n;
	}

}
