#include "cholesky_opt.cpp"
#include <tuple>

template <typename scalar_type>
std::tuple<matrix<scalar_type>,matrix<scalar_type>> dolittle_decomposition(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> upper(n, n);
    matrix<scalar_type> lower(n, n);

    for (size_t i = 0; i < n; i++){
        for (size_t k = i; k < n; k++){
            scalar_type sum = 0;
            for (size_t j = 0; j < i; j++){
                sum += (lower(i,j) * upper(j,k));
            }
            upper(i,k) = input(i,k) - sum;
        }
        for (size_t k = i; k < n; k++){
            if (i == k) {
                lower(i, i) = 1;
            }else{
                scalar_type sum = 0;
                for (size_t j = 0; j < i; j++) {
                    sum += (lower(k, j) * upper(j, i));
                }
                lower(k,i) = (input(k,i) - sum) / upper(i,i);
            }
        }
    }

    return std::make_tuple(upper,lower);
}