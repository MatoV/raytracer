#include "Core/Camera.h"
#include "Math/Vector/Vector.h"
#include "Core/Scene/Scene.h"
#include "Core/Canvas.h"

namespace mtr {


	Camera::Camera(int hSize, int vSize, float fieldOfView) : m_hSize{ hSize }, m_vSize{ vSize }, m_fov{ fieldOfView }, m_transform{ 1 }, m_invTransform{ 1 }{
		auto halfView = tan(m_fov / 2.0);
		float aspect = (float)m_hSize / m_vSize;
		if (aspect >= 1) {
			m_halfWidth = halfView;
			m_halfHeight = halfView / aspect;
		}
		else {
			m_halfWidth = halfView * aspect;
			m_halfHeight = halfView;
		}
		m_pixelSize = (m_halfWidth * 2.0) / m_hSize;
	}

	Ray<float> Camera::RayForPixel(int px, int py) const {
		// offset from the edge of canvas to the pixel's center
		float xoffset = (px + 0.5f) * m_pixelSize;
		float yoffset = (py + 0.5f) * m_pixelSize;
		
		float worldX = m_halfWidth - xoffset;
		float worldY = m_halfHeight - yoffset;

		auto pixel = m_invTransform * Point(worldX, worldY, -1.f);
		auto origin = m_invTransform * Point(0.f, 0.f, 0.f);
		auto direction = Normalize(pixel - origin);

		return Ray<float>{origin, direction};
	}

	Canvas Camera::Render(const Scene& scene) const {
		Canvas canvas{ m_hSize, m_vSize };
		for (auto y = 0; y < m_vSize; ++y) {
			for (auto x = 0; x < m_hSize; ++x) {
				auto ray = RayForPixel(x, y);
				auto color = ColorAt(scene, ray);
				canvas.WritePixel(x, y, color);
			}
		}
		return canvas;
	}

}