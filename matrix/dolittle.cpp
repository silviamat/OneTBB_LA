#include "cholesky_seq.cpp"
#include <tuple>

template <typename scalar_type>
std::tuple<matrix<scalar_type>,matrix<scalar_type>> dolittle_decomposition(const matrix<scalar_type>& input) {
    assert(input.rows() == input.columns());
    size_t n = input.rows();
    matrix<scalar_type> upper(n, n);
    matrix<scalar_type> lower(n, n);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t k = i; k < n; k++)
        {
            scalar_type sum = 0;
            for (size_t j = 0; j < i; j++)
                sum += (lower(i,j) * upper(j,k));
            upper(i,k) = input(i,k) - sum;
        }
        for (size_t k = i; k < n; k++)
        {
            if (i == k)
                lower(i,i) = 1;
            else
            {
                scalar_type sum = 0;
                for (size_t j = 0; j < i; j++)
                    sum += (lower(k,j) * upper(j,i));
                lower(k,i) = (input(k,i) - sum) / upper(i,i);
            }
        }
    }

    return std::make_tuple(upper,lower);
}

template <typename scalar_type>
void print_LU_decomposition(const matrix<scalar_type>& matrix) {
    std::cout << "Matrix:\n";
    print(std::cout, matrix);
    std::cout << "LU Decomposition:\n";
    size_t n = matrix.rows();
    ::matrix<scalar_type> upper(n,n),lower(n,n);
    std::tie(upper,lower)=dolittle_decomposition(matrix);
    std::cout << "Upper Triangular:\n";
    print(std::cout,upper);
    std::cout << "Lower Triangular:\n";
    print(std::cout,lower);
}