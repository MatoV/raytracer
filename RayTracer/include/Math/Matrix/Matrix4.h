#pragma once
#include <iostream>
#include <concepts>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include "Math/CMath.h"
#include "Math/Vector/Vector.h"

namespace mtr {

	template<int_or_float T = float>
	class Matrix4 {
	public:

		Matrix4();
		/* Initialing matrix with a value of 1 creates identity matrix, otherwise it fills the matrix with a given value */
		Matrix4(T value);
		Matrix4(T* elements);
		Matrix4(const Matrix4<T>& other);

		//Matrix4(std::initializer_list<std::initializer_list<T>> elements);

		/* Access operators */
		const T operator()(size_t row, size_t column) const {
			if (row < 0 || row >= rows || column < 0 || column >= cols)
				throw std::out_of_range("Matrix index out of bounds.");
			return data[row * cols + column];
		}
		T& operator()(size_t row, size_t column)  {
			if (row < 0 || row >= rows || column < 0 || column >= cols)
				throw std::out_of_range("Matrix index out of bounds.");
			return data[row * cols + column];
		}
		/* Assignment */
		Matrix4<T>& operator=(const Matrix4<T>& other) {
			if (this == &other) return *this;
			std::copy(other.data, other.data + rows * cols, data);
			return *this;
		}
		/* Matrix multiplication */
		Matrix4<T>& operator*=(const Matrix4<T>& rhs) {
			Matrix4<T> m{};
			for (auto i = 0; i < rows; ++i) {
				for (auto j = 0; j < cols; ++j) {
					for (auto p = 0; p < rows; ++p) {
						m(i, j) += (*this)(i, p) * rhs(p, j);
					}
					m(i, j) = IsZero(m(i, j)) ? T(0) : m(i, j);
				}
			}
			(*this) = m;
			return *this;
		}
		friend Matrix4<T> operator*(Matrix4<T> lhs, const Matrix4<T> rhs) {
			lhs *= rhs;
			return lhs;
		}
		friend Vector<T> operator*(Matrix4<T> lhs, const Vector<T> rhs) {
			Vector<T> v{};
			for (auto i = 0; i < lhs.length; ++i) {
				for (auto j = 0; j < lhs.length; ++j) {
					//for (auto p = 0; p < lhs.length; ++p) {
						v[i] += lhs(i, j) * rhs[j];
					//}
					
				}
				v[i] = IsZero(v[i]) ? T(0) : v[i];
			}
			return v;
		}
		Matrix4<T>& operator*=(T value) {
			for (auto i = 0; i < rows; ++i) {
				for (auto j = 0; j < cols; ++j) {
					(*this)(i, j) *= value;
				}
			}
			return *this;
		}
		friend Matrix4<T> operator*(Matrix4<T> lhs, T rhs) {
			lhs *= rhs;
			return lhs;
		}
		friend Matrix4<T> operator*(T lhs, Matrix4<T> rhs) {
			rhs *= lhs;
			return rhs;
		}
		/* Comparison operators */
		friend bool operator==(const Matrix4<T>& lhs, const Matrix4<T>& rhs) {
			for (auto i = 0; i < lhs.length; ++i) {
				for (auto j = 0; j < lhs.length; ++j) {
					if (!IsEqual(rhs(i, j), lhs(i, j)))
						return false;
				}
			}
			return true;
		}
		friend bool operator!=(const Matrix4<T>& lhs, const Matrix4<T>& rhs) {
			return !(lhs==rhs);
		}



		/* Transforms this matrix to an identity matrix and returns the refrence */
		Matrix4<T>& ToIdentity();
		
		constexpr static size_t length = 4;

	private:
		const size_t rows{4};
		const size_t cols{4};
		T data[16];

	};


	template<int_or_float T>
	Matrix4<T>::Matrix4() : Matrix4(static_cast<T>(0)){}

	template<int_or_float T>
	Matrix4<T>::Matrix4(T value) {
		if (static_cast<int>(value) == 1) {
			this->ToIdentity();
			return;
		}
		for (auto i = 0; i < rows*cols; ++i) {
			data[i] = value;
		}
	}

	template<int_or_float T>
	Matrix4<T>::Matrix4(T* elements) {
		for (auto i = 0; i < rows * cols; ++i) {
			data[i] = elements[i];
		}
	}

	template<int_or_float T>
	Matrix4<T>::Matrix4(const Matrix4<T>& other) {
		std::copy(other.data, other.data + rows * cols, data);
	}


	//template<matrix_req T>
	//Matrix4<T>::Matrix4(std::initializer_list<std::initializer_list<T>> elements) : Matrix4() {
	//	for (auto i = 0; i < rows; ++i) {
	//		for (auto j = 0; j < cols; ++j) {
	//			data[i * cols + j] = ((elements.begin() + i)->begin())[j];
	//		}
	//	}
	//}

	template<int_or_float T>
	Matrix4<T>& Matrix4<T>::ToIdentity() {
		for (auto i = 0; i < rows; ++i) {
			for (auto j = 0; j < cols; ++j) {
				if (i == j) data[i* cols + j] = static_cast<T>(1);
				else data[i * cols + j] = 0;
			}
		}
		return *this;
	}

}