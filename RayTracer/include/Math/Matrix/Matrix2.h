#pragma once
#include <iostream>
#include <concepts>
#include <memory>
#include <algorithm>
#include <ranges>
#include <stdexcept>
#include "Math/CMath.h"
#include "Math/Vector/Vector.h"

namespace mtr {


	template<int_or_float T = float>
	class Matrix2 {
	public:

		Matrix2();
		/* Initialing matrix with a value 1 creates identity matrix, otherwise it fills the matrix with a given value */
		Matrix2(T value);
		Matrix2(T* elements);
		Matrix2(const Matrix2<T>& other);

		//Matrix2(std::initializer_list<std::initializer_list<T>> elements);

		/* Access operators */
		const T operator()(size_t row, size_t column) const {
			if (row < 0 || row >= rows || column < 0 || column >= cols)
				throw std::out_of_range("Matrix index out of bounds.");
			return data[row * cols + column];
		}
		T& operator()(size_t row, size_t column) {
			if (row < 0 || row >= rows || column < 0 || column >= cols)
				throw std::out_of_range("Matrix index out of bounds.");
			return data[row * cols + column];
		}
		/* Assignment */
		Matrix2<T>& operator=(const Matrix2<T>& other) {
			if (this == &other) return *this;
			std::copy(other.data, other.data + rows * cols, data);
			return *this;
		}
		/* Matrix multiplication */
		Matrix2<T>& operator*=(const Matrix2<T>& rhs) {
			Matrix2<T> m{};
			for (auto i = 0; i < rows; ++i) {
				for (auto j = 0; j < cols; ++j) {
					for (auto p = 0; p < rows; ++p) {
						m(i, j) += (*this)(i, p) * rhs(p, j);
					}
				}
			}
			(*this) = m;
			return *this;
		}
		friend Matrix2<T> operator*(Matrix2<T> lhs, const Matrix2<T> rhs) {
			lhs *= rhs;
			return lhs;
		}
		Matrix2<T>& operator*=(T value) {
			for (auto i = 0; i < rows; ++i) {
				for (auto j = 0; j < cols; ++j) {
					(*this)(i, j) *= value;
				}
			}
			return *this;
		}
		friend Matrix2<T> operator*(Matrix2<T> lhs, T rhs) {
			lhs *= rhs;
			return lhs;
		}
		friend Matrix2<T> operator*(T lhs, Matrix2<T> rhs) {
			rhs *= lhs;
			return rhs;
		}
		/* Comparison operators */
		friend bool operator==(const Matrix2<T>& lhs, const Matrix2<T>& rhs) {
			for (auto i = 0; i < lhs.length; ++i) {
				for (auto j = 0; j < lhs.length; ++j) {
					if (!IsEqual(rhs(i, j), lhs(i, j)))
						return false;
				}
			}
			return true;
		}
		friend bool operator!=(const Matrix2<T>& lhs, const Matrix2<T>& rhs) {
			return !(lhs == rhs);
		}

		/* Transforms this matrix to an identity matrix and returns the refrence */
		Matrix2<T>& ToIdentity();

		constexpr static size_t length = 2;

	private:
		const size_t rows{ 2 };
		const size_t cols{ 2 };
		T data[4];

	};


	template<int_or_float T>
	Matrix2<T>::Matrix2() : Matrix2(static_cast<T>(0)) {}

	template<int_or_float T>
	Matrix2<T>::Matrix2(T value) {
		if (static_cast<int>(value) == 1) {
			this->ToIdentity();
			return;
		}
		for (auto i = 0; i < rows * cols; ++i) {
			data[i] = value;
		}
	}

	template<int_or_float T>
	Matrix2<T>::Matrix2(T* elements) {
		for (auto i = 0; i < rows * cols; ++i) {
			data[i] = elements[i];
		}
	}

	template<int_or_float T>
	Matrix2<T>::Matrix2(const Matrix2<T>& other) {
		std::copy(other.data, other.data + rows * cols, data);
	}


	//template<int_or_float T>
	//Matrix2<T>::Matrix2(std::initializer_list<std::initializer_list<T>> elements) : Matrix2() {
	//	for (auto i = 0; i < rows; ++i) {
	//		for (auto j = 0; j < cols; ++j) {
	//			data[i * cols + j] = ((elements.begin() + i)->begin())[j];
	//		}
	//	}
	//}

	template<int_or_float T>
	Matrix2<T>& Matrix2<T>::ToIdentity() {
		for (auto i = 0; i < rows; ++i) {
			for (auto j = 0; j < cols; ++j) {
				if (i == j) data[i * cols + j] = static_cast<T>(1);
				else data[i * cols + j] = 0;
			}
		}
		return *this;
	}

}