#include "dolittle.cpp"

int main() {
    // Cholesky
    matrix<double> matrix1(3, 3,
                           {{25, 15, -5},
                            {15, 18, 0},
                            {-5, 0, 11}});
    print_cholesky_factor(matrix1);

    matrix<double> matrix2(3, 3,
                           {{4, 12, -16},
                            {12, 37, -43},
                            {-16, -43, 98}});
    print_cholesky_factor(matrix2);

    matrix<double> matrix3(4, 4,
                           {{18, 22, 54, 42},
                            {22, 70, 86, 62},
                            {54, 86, 174, 134},
                            {42, 62, 134, 106}});
    print_cholesky_factor(matrix3);

    // LU
    matrix<double> matrix4(3, 3,
                           {{2, -1, -2},
                            {-4, 6, 3},
                            {-4, -2, 8}});
    print_LU_decomposition(matrix4);

    return 0;
}