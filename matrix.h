#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

struct MatrixOutOfRange : public std::out_of_range {
    MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {}
};

struct MatrixIsDegenerateError : public std::runtime_error {
    MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {}
};

template <typename T, size_t N, size_t M>
class Matrix {
public:
    T data[N][M] = {};

    size_t RowsNumber() const {
        return N;
    }

    size_t ColumnsNumber() const {
        return M;
    }

    T& operator()(size_t row, size_t col) {
        return data[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        return data[row][col];
    }

    T& At(size_t row, size_t col) {
        if (row >= N || col >= M) {
            throw MatrixOutOfRange{};
        }
        return data[row][col];
    }

    const T& At(size_t row, size_t col) const {
        if (row >= N || col >= M) {
            throw MatrixOutOfRange{};
        }
        return data[row][col];
    }

    Matrix& operator+=(const Matrix& other) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    template <size_t K>
    Matrix<T, N, K> operator*(const Matrix<T, M, K>& other) const {
        Matrix<T, N, K> result{};
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < K; ++j) {
                for (size_t k = 0; k < M; ++k) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    Matrix& operator*=(const Matrix<T, M, M>& other) {
        *this = *this * other;
        return *this;
    }

    Matrix& operator*=(T scalar) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix& operator/=(T scalar) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] /= scalar;
            }
        }
        return *this;
    }

    bool operator==(const Matrix& other) const {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                if (data[i][j] != other.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }
};

template <typename T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& matrix) {
    Matrix<T, M, N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            result(j, i) = matrix(i, j);
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> lhs, const Matrix<T, N, M>& rhs) {
    lhs += rhs;
    return lhs;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M> lhs, const Matrix<T, N, M>& rhs) {
    lhs -= rhs;
    return lhs;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator*(Matrix<T, N, M> matrix, T scalar) {
    matrix *= scalar;
    return matrix;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator*(T scalar, Matrix<T, N, M> matrix) {
    matrix *= scalar;
    return matrix;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator/(Matrix<T, N, M> matrix, T scalar) {
    matrix /= scalar;
    return matrix;
}

template <typename T, size_t N, size_t M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& matrix) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            in >> matrix(i, j);
        }
    }
    return in;
}

template <typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& matrix) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (j != 0) {
                out << ' ';
            }
            out << matrix(i, j);
        }
        if (i != N - 1) {
            out << '\n';
        }
    }
    return out;
}

#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

template <typename T, size_t N>
void Transpose(Matrix<T, N, N>& matrix) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i + 1; j < N; ++j) {
            std::swap(matrix(i, j), matrix(j, i));
        }
    }
}

template <typename T, size_t N>
T Trace(const Matrix<T, N, N>& matrix) {
    T trace = T();
    for (size_t i = 0; i < N; ++i) {
        trace += matrix(i, i);
    }
    return trace;
}

template <typename T>
T Abs(const T& value) {
    return value < T() ? -value : value;
}

template <typename T, size_t N>
T Determinant(Matrix<T, N, N> matrix) {
    T det = T(1);
    for (size_t i = 0; i < N; ++i) {
        size_t pivot = i;
        for (size_t j = i + 1; j < N; ++j) {
            if (Abs(matrix(j, i)) > Abs(matrix(pivot, i))) {
                pivot = j;
            }
        }
        if (pivot != i) {
            for (size_t j = 0; j < N; ++j) {
                std::swap(matrix(i, j), matrix(pivot, j));
            }
            det = -det;
        }
        if (matrix(i, i) == T()) {
            return T();
        }
        det *= matrix(i, i);
        for (size_t j = i + 1; j < N; ++j) {
            T factor = matrix(j, i) / matrix(i, i);
            for (size_t k = i; k < N; ++k) {
                matrix(j, k) -= factor * matrix(i, k);
            }
        }
    }
    return det;
}

template <typename T, size_t N>
Matrix<T, N, N> GetInversed(Matrix<T, N, N> matrix) {
    Matrix<T, N, N> inverse{};
    for (size_t i = 0; i < N; ++i) {
        inverse(i, i) = T(1);
    }

    for (size_t i = 0; i < N; ++i) {
        size_t pivot = i;
        for (size_t j = i + 1; j < N; ++j) {
            if (Abs(matrix(j, i)) > Abs(matrix(pivot, i))) {
                pivot = j;
            }
        }
        if (matrix(pivot, i) == T()) {
            throw MatrixIsDegenerateError{};
        }
        if (pivot != i) {
            for (size_t j = 0; j < N; ++j) {
                std::swap(matrix(i, j), matrix(pivot, j));
                std::swap(inverse(i, j), inverse(pivot, j));
            }
        }

        T divisor = matrix(i, i);
        for (size_t j = 0; j < N; ++j) {
            matrix(i, j) /= divisor;
            inverse(i, j) /= divisor;
        }

        for (size_t j = 0; j < N; ++j) {
            if (j != i && matrix(j, i) != T()) {
                T factor = matrix(j, i);
                for (size_t k = 0; k < N; ++k) {
                    matrix(j, k) -= factor * matrix(i, k);
                    inverse(j, k) -= factor * inverse(i, k);
                }
            }
        }
    }

    return inverse;
}

template <typename T, size_t N>
void Inverse(Matrix<T, N, N>& matrix) {
    matrix = GetInversed(matrix);
}

#endif