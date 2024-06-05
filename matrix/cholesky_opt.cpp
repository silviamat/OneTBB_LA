#include "cholesky_seq.cpp"
#include <tbb/tbb.h>

template <typename scalar_type>
matrix<scalar_type> cholesky_factor_opt(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> result(n, n);

    for (size_t i = 0; i < n; ++i) {
        scalar_type value_diag = input(i, i);
        tbb::parallel_for(size_t(0), i, [&](size_t k){
            scalar_type value = input(i, k);
            for (size_t j = 0; j < k; ++j) {
                value -= result(i, j) * result(k, j);
            }
            result(i, k) = value/result(k, k);
            value_diag -= result(i,k)*result(i,k);
        });
        result(i, i) = std::sqrt(value_diag);
    }
    return result;
}