#pragma once
#include "CMath.h"
#include "Matrix4.h"
#include "MatrixTransform.h"
#include "Ray.h"


namespace mtr {

	class Scene;
	class Canvas;

	class Camera {

	public:

		Camera() : Camera(160,120, M_PI_2) {};

		/* Constructs a camera with given dimensions and field of view (in radians) */
		Camera(int hSize, int vSize, float fieldOfView);

		/* Returns transformation matrix */
		const Matrix4<float> GetTransform() const { return m_transform; };

		/* Returns inverse transformation matrix */
		const Matrix4<float> GetInvTransform() const { return m_invTransform; };

		/* Sets the transformation matrix to a given value */
		void SetTransform(Matrix4<float> matrix) { m_transform = matrix; m_invTransform = Inverse(matrix); };

		/* Returns ray that goes through a pixel */
		Ray<float> RayForPixel(int px, int py) const;

		/* Renders given scene to a canvas */
		Canvas Render(const Scene& scene) const;

		auto GetPixelSize() const { return m_pixelSize; };
		auto GetCamFov() const { return m_fov; };
		auto GetWidth() const { return m_hSize; };
		auto GetHeight() const { return m_vSize; };

	private:
		int m_hSize;
		int m_vSize;
		float m_halfWidth;
		float m_halfHeight;
		float m_pixelSize;
		float m_fov;
		Matrix4<float> m_transform;
		Matrix4<float> m_invTransform;
		
	};


}
