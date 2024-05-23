#include "dolittle_seq.cpp"
#include <tuple>

template <typename scalar_type>
std::tuple<matrix<scalar_type>,matrix<scalar_type>> dolittle_decomposition_opt(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> upper(n, n);
    matrix<scalar_type> lower(n, n);

    for (size_t i = 0; i < n; i++){
        tbb::parallel_for(size_t(0), n, [&](size_t k){
            scalar_type sum = 0;
            for (size_t j = 0; j < i; j++){
                sum += (lower(i,j) * upper(j,k));
            }
            upper(i,k) = input(i,k) - sum;
        });
        tbb::parallel_for(size_t(0), n, [&](size_t k){
            if (i == k) {
                lower(i, i) = 1;
            }else{
                scalar_type sum = 0;
                for (size_t j = 0; j < i; j++) {
                    sum += (lower(k, j) * upper(j, i));
                }
                lower(k,i) = (input(k,i) - sum) / upper(i,i);
            }
        });
    }

    return std::make_tuple(upper,lower);
}