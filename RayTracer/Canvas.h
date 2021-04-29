#pragma once

#include <unordered_map>
#include <vector>
#include "Vector.h"


namespace mtr {


	class Canvas {
	public:

		explicit Canvas(size_t width, size_t height);

		/* Returns width of a canvas */
		size_t GetWidth() { return width; }

		/* Returns height of a canvas */
		size_t GetHeight() { return height; }

		/* Set new size of a canvas */
		void SetSize(int width, int height) { this->width = width; this->height = height; }

		/* 
		/*	Writes color to a pixel on a given coordinate 
		*	Colors are in RGB space (values between 0 and 1)
		*/
		void WritePixel(int x, int y, mtr::Vector<float> color = { 0.f,0.f,0.f });

		/* Returns a color of a pixel at x,y coordinates*/
		mtr::Vector<float>& PixelAt(int x, int y) ;

		/* Saves canvas as an image (ppm format) */
		bool SaveToFile();



	private:

		int floatTo255RGB(float c);

		/* Canvas width and height */
		size_t width, height;

		/* Array of pixels */
		std::vector<mtr::Vector<float>> pixels;
	};

}