#pragma once
#include <iostream>
#include <concepts>
#include <memory>
#include <algorithm>
#include <ranges>
#include "Math/CMath.h"
#include "Math/Vector/Vector.h"

namespace mtr {

	template<int_or_float T = float>
	class Matrix3 {
	public:

		Matrix3();
		/* Initialing matrix with a value 1 creates identity matrix, otherwise it fills the matrix with a given value */
		Matrix3(T value);
		Matrix3(T* elements);
		Matrix3(const Matrix3<T>& other);

		//Matrix3(std::initializer_list<std::initializer_list<T>> elements);

		/* Access operators */
		const T operator()(size_t row, size_t column) const {
			if (row < 0 || row >= rows || column < 0 || column >= cols)
				throw std::domain_error("Matrix index out of range.");
			return data[row * cols + column];
		}
		T& operator()(size_t row, size_t column) {
			if (row < 0 || row >= rows || column < 0 || column >= cols)
				throw std::domain_error("Matrix index out of range.");
			return data[row * cols + column];
		}
		/* Assignment */
		Matrix3<T>& operator=(const Matrix3<T>& other) {
			if (this == &other) return *this;
			std::copy(other.data, other.data + rows * cols, data);
			return *this;
		}
		/* Matrix multiplication */
		Matrix3<T>& operator*=(const Matrix3<T>& rhs) {
			Matrix3<T> m{};
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
		friend Matrix3<T> operator*(Matrix3<T> lhs, const Matrix3<T> rhs) {
			lhs *= rhs;
			return lhs;
		}
		Matrix3<T>& operator*=(T value) {
			for (auto i = 0; i < rows; ++i) {
				for (auto j = 0; j < cols; ++j) {
					(*this)(i, j) *= value;
				}
			}
			return *this;
		}
		friend Matrix3<T> operator*(Matrix3<T> lhs, T rhs) {
			lhs *= rhs;
			return lhs;
		}
		friend Matrix3<T> operator*(T lhs, Matrix3<T> rhs) {
			rhs *= lhs;
			return rhs;
		}
		/* Comparison operators */
		friend bool operator==(const Matrix3<T>& lhs, const Matrix3<T>& rhs) {
			for (auto i = 0; i < lhs.length; ++i) {
				for (auto j = 0; j < lhs.length; ++j) {
					if (!IsEqual(rhs(i, j), lhs(i, j)))
						return false;
				}
			}
			return true;
		}
		friend bool operator!=(const Matrix3<T>& lhs, const Matrix3<T>& rhs) {
			return !(lhs == rhs);
		}


		/* Transforms this matrix to an identity matrix and returns the refrence */
		Matrix3<T>& ToIdentity();

		constexpr static size_t length = 3;

	private:
		const size_t rows{ 3 };
		const size_t cols{ 3 };
		T data[9];

	};


	template<int_or_float T>
	Matrix3<T>::Matrix3() : Matrix3(static_cast<T>(0)) {}

	template<int_or_float T>
	Matrix3<T>::Matrix3(T value) {
		if (static_cast<int>(value) == 1) {
			this->ToIdentity();
			return;
		}
		for (auto i = 0; i < rows * cols; ++i) {
			data[i] = value;
		}
	}

	template<int_or_float T>
	Matrix3<T>::Matrix3(T* elements) {
		for (auto i = 0; i < rows * cols; ++i) {
			data[i] = elements[i];
		}
	}

	template<int_or_float T>
	Matrix3<T>::Matrix3(const Matrix3<T>& other) {
		std::copy(other.data, other.data + rows * cols, data);
	}


	//template<int_or_float T>
	//Matrix3<T>::Matrix3(std::initializer_list<std::initializer_list<T>> elements) : Matrix3() {
	//	for (auto i = 0; i < rows; ++i) {
	//		for (auto j = 0; j < cols; ++j) {
	//			data[i * cols + j] = ((elements.begin() + i)->begin())[j];
	//		}
	//	}
	//}

	template<int_or_float T>
	Matrix3<T>& Matrix3<T>::ToIdentity() {
		for (auto i = 0; i < rows; ++i) {
			for (auto j = 0; j < cols; ++j) {
				if (i == j) data[i * cols + j] = static_cast<T>(1);
				else data[i * cols + j] = 0;
			}
		}
		return *this;
	}

}