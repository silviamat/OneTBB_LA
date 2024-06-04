#include "cholesky_seq.cpp"
#include <tbb/tbb.h>

template <typename scalar_type>
matrix<scalar_type> cholesky_factor_opt(const matrix<scalar_type>& input) {
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