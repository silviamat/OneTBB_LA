#include "matrix.cpp"

template <typename scalar_type>
matrix<scalar_type> cholesky_factor(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> result{n, n};

    for (size_t i = 0; i < n; ++i) {
        for (size_t k = 0; k < i; ++k) {
            scalar_type value = input(i, k);
            for (size_t j = 0; j < k; ++j) {
                value -= result(i, j) * result(k, j);
            }
            result(i, k) = value/result(k, k);
        }
        scalar_type value = input(i, i);
        for (size_t j = 0; j < i; ++j) {
            value -= result(i, j) * result(i, j);
        }
        result(i, i) = std::sqrt(value);
    }
    return result;
}