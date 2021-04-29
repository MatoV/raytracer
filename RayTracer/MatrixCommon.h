#pragma once

#include "Matrix4.h"
#include "Matrix3.h"
#include "Matrix2.h"

namespace mtr {

	template<typename M>
	concept matrix_len = requires { std::same_as<const size_t, M>; } && M::length >= 2;

	/* Returns the transposed matrix of m */
	template<int_or_float T, template<typename C> class M>
	M<T> Transpose(const M<T>& m) {
		M<T> transposed{};
		for (auto i = 0; i < m.length; ++i) {
			for (auto j = 0;  j < m.length;  ++j) {
				transposed(i, j) = m(j, i);
			}
		}
		return transposed;
	}

	/*	Returns the inversed matrix of m 
	*	If inverse doesn't exist, returns zero matrix
	*/
	template<int_or_float T, template<typename C> class M>
	M<T> Inverse(const M<T>& m) {
		M<T> inversed{};
		
		T det = Determinant(m);
		if (!IsEqual(det, static_cast<T>(0))) {
			for (auto r = 0; r < m.length; ++r) {
				for (auto c = 0; c < m.length; ++c) {
					auto cof = Cofactor(m, r, c);
					inversed(c, r) = cof / det;
				}
			}
		}
		return inversed;
	}

	/* Returns determinant of a given matrix */
	template<typename T, template<typename C> class M>
	requires (int_or_float<T> && matrix_len<M<T>>)
	T Determinant(const M<T>& m) {
		T det{0};
		if (m.length == 2) {
			det = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
		}
		else {
			for (auto c = 0; c < m.length; ++c) {
				det += m(0, c) * Cofactor(m, 0, c);
			}
		}
		return det;
	}

	/* Returns submatrix of a given 4x4 matrix */
	template<int_or_float T>
	Matrix3<T> Submatrix(const Matrix4<T>& m, int row, int column) {
		T arr[9]{};
		size_t i = 0;
		for (auto r = 0; r < m.length; ++r) {
			if (r == row) continue;
			for (auto c = 0; c < m.length; ++c) {
				if (c == column) continue;
				arr[i] = m(r, c);
				++i;
			}
		}
		return Matrix3<T>{arr};
	}
	
	/* Returns submatrix of a given 3x3 matrix */
	template<int_or_float T>
	Matrix2<T> Submatrix(const Matrix3<T>& m, int row, int column) {
		T arr[4]{};
		size_t i = 0;
		for (auto r = 0; r < m.length; ++r) {
			if (r == row) continue;
			for (auto c = 0; c < m.length; ++c) {
				if (c == column) continue;
				arr[i] = m(r, c);
				++i;
			}
		}
		return Matrix2<T>{arr};
	}

	template<int_or_float T>
	Matrix2<T> Submatrix(const Matrix2<T>& m, int row, int column) {
		T arr[4]{};
		std::cerr << "Submatrix of a 2x2 matrix does not exist.\n";
		return Matrix2<T>{arr};
	}


	template<typename T, template<typename C> class M>
	requires (int_or_float<T> && matrix_len<M<T>>)
	T Minor(const M<T>& m, int row, int column) {
		return Determinant(Submatrix(m, row, column));
	}

	template<typename T, template<typename C> class M>
	requires (int_or_float<T> && matrix_len<M<T>>)
	T Cofactor(const M<T>& m, int row, int column) {
		return (row + column) % 2 ? -Minor(m, row, column) : Minor(m, row, column);
	}


}