#include "matrix/dolittle_opt.cpp"
#include <gtest/gtest.h>

namespace {
    TEST(utest, sym){
        matrix<int> matrix1 = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/d750.O");
        EXPECT_EQ((matrix1.is_symmetric()), 1);
    }

    TEST(utest, cholesky_seq) {
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        matrix cholesky = cholesky_factor(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_seq_large) {
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_1000.txt");
        matrix<double> cholesky = cholesky_factor(matrix1);
        matrix<double> matrix2 = cholesky * cholesky.transpose();
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_opt) {
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        matrix cholesky = cholesky_factor_for(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    /*TEST(utest, cholesky_opt_large) {
        matrix<int> matrix1 = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/d750.O");
        matrix cholesky = cholesky_factor_opt(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }*/

    /*TEST(utest, LU_seq) {
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        std::tuple<matrix<double>, matrix<double>> result = dolittle_decomposition(matrix1);
        EXPECT_EQ((matrix1 == get<1>(result)*get<0>(result)), 1);
    }

    TEST(utest, LU_seq_large) {
        matrix<int> matrix1 = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/d750.O");
        std::tuple<matrix<int>, matrix<int>> result = dolittle_decomposition(matrix1);
        EXPECT_EQ((matrix1 == get<1>(result)*get<0>(result)), 1);
    }

    TEST(utest, LU_opt) {
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        std::tuple<matrix<double>, matrix<double>> result = dolittle_decomposition_opt(matrix1);
        EXPECT_EQ((matrix1 == get<1>(result)*get<0>(result)), 1);
    }

    TEST(utest, LU_opt_large) {
        matrix<int> matrix1 = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/d750.O");
        std::tuple<matrix<int>, matrix<int>> result = dolittle_decomposition(matrix1);
        EXPECT_EQ((matrix1 == get<1>(result)*get<0>(result)), 1);
    }*/
}