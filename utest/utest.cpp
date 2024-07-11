#include "matrix/cholesky_opt.cpp"
#include <gtest/gtest.h>

namespace {
    TEST(utest, sym){
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_1000.txt");
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
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_100.txt");
        matrix<double> cholesky = cholesky_factor(matrix1);
        matrix<double> matrix2 = cholesky * cholesky.transpose();
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_for) {
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        matrix cholesky = cholesky_factor_for(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_reduce) {
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        matrix cholesky = cholesky_factor_reduce(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_for_each) {
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        matrix cholesky = cholesky_factor_for_each(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_for_large) {
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_1000.txt");
        matrix cholesky = cholesky_factor_for(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_for_each_large) {
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_1000.txt");
        matrix cholesky = cholesky_factor_for_each(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }

    TEST(utest, cholesky_reduce_large) {
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_100.txt");
        matrix cholesky = cholesky_factor_reduce(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }
}