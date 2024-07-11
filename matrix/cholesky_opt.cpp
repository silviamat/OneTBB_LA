#include "cholesky_seq.cpp"
#include <tbb/tbb.h>

/*template <typename scalar_type>
matrix<scalar_type> cholesky_factor_for(const matrix<scalar_type>& input) {
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
}*/

template <typename scalar_type>
matrix<scalar_type> cholesky_factor_reduce(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> result(n, n);

    for (size_t i = 0; i < n; ++i) {
        scalar_type value_diag = input(i, i);
        for (size_t k = 0; k < i; ++k){
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
            result(i, k) = value/result(k, k);
            value_diag -= result(i,k)*result(i,k);
        }
        result(i, i) = std::sqrt(value_diag);
    }
    return result;
}

template <typename scalar_type>
matrix<scalar_type> cholesky_factor_for_each(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> result(n, n);

    using ElementIndex = std::pair<size_t,size_t>;
    ElementIndex origin(0,0);

    tbb::parallel_for_each(&origin, &origin+1, [&] (const ElementIndex& i, tbb::feeder<ElementIndex> &feeder){
        if(i.first == i.second){
            scalar_type value = input(i.first, i.first);
            for (size_t j = 0; j < i.first; ++j) {
                value -= result(i.first, j) * result(i.first, j);
            }
            result(i.first, i.first) = std::sqrt(value);
            if(i.first+1 < n){
                feeder.add(ElementIndex(i.first + 1, 0));
            }
        }else{
            scalar_type value = input(i.first, i.second);
            for (size_t j = 0; j < i.second; ++j) {
                value -= result(i.first, j) * result(i.second, j);
            }
            result(i.first, i.second) = value/result(i.second, i.second);
            feeder.add(ElementIndex(i.first, i.second + 1));
        }
    });

    return result;
}