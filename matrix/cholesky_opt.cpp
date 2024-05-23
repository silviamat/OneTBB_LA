#include "cholesky_seq.cpp"
#include <tbb/tbb.h>

template <typename scalar_type>
matrix<scalar_type> cholesky_factor_opt(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> result(n, n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t k = 0; k < i; ++k) {
            scalar_type value = input(i, k);
            scalar_type reduction_value = tbb::parallel_reduce(
                    tbb::blocked_range<size_t>(size_t(0), k),
                    scalar_type(0),
                    [&](const tbb::blocked_range<size_t>& r, scalar_type init) -> scalar_type {
                        for (size_t j = r.begin(); j < r.end(); ++j) {
                            init += result(i, j) * result(k, j);
                        }
                        return init;
                    },
                    [](scalar_type x, scalar_type y) -> scalar_type { return x + y; }
            );
            value -= reduction_value;
            result(i, k) = value / result(k, k);
        }
        scalar_type value = input(i, i);
        scalar_type reduction_value = tbb::parallel_reduce(
                tbb::blocked_range<size_t>(size_t(0), i),
                scalar_type(0),
                [&](const tbb::blocked_range<size_t>& r, scalar_type init) -> scalar_type {
                    for (size_t j = r.begin(); j < r.end(); ++j) {
                        init += result(i, j) * result(i, j);
                    }
                    return init;
                },
                [](scalar_type x, scalar_type y) -> scalar_type { return x + y; }
        );
        value -= reduction_value;
        result(i, i) = std::sqrt(value);
    }
    return result;
}