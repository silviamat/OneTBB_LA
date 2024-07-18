#include "matrix/cholesky_opt.cpp"
#include <gtest/gtest.h>

namespace {
    TEST(utest, constructors){
        matrix<double> matrix1 (3,3);
        matrix<double> matrix2 (3,3,0);
        matrix<double> matrix3(3, 3,
                            {{25, 15, -5},
                             {15, 18, 0},
                             {-5, 0,  11}});
    }

    TEST(utest, accesors){
        matrix<double> matrix(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        EXPECT_EQ((matrix.rows()==3)&&(matrix.columns()==3)&&(matrix.size()==9), 1);
    }

    TEST(utest, parenthesis){
        matrix<double> matrix(3, 3,
                              {{25, 15, -5},
                               {15, 18, 0},
                               {-5, 0,  11}});
        EXPECT_EQ((matrix(1,1)==18), 1);
    }

    TEST(utest, bracket){
        matrix<double> matrix(3, 3,
                              {{25, 15, -5},
                               {15, 18, 0},
                               {-5, 0,  11}});
        EXPECT_EQ((matrix[4]==18), 1);
    }

    TEST(utest, equal){
        matrix<double> matrix1(3, 3,
                              {{25, 15, -5},
                               {15, 18, 0},
                               {-5, 0,  11}});
        matrix<double> matrix2(3, 3,
                              {{25, 15, -5},
                               {15, 18, 0},
                               {-5, 0,  11}});
        EXPECT_EQ((matrix1==matrix2), 1);
    }

    TEST(utest, not_equal){
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        matrix<double> matrix2(3, 3,
                               {{25, 10, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        EXPECT_EQ((matrix1==matrix2), 0);
    }

    TEST(utest, mult){
        matrix<double> matrix1(2,2,{{1,0},{0,1}});
        matrix<double> matrix2(2,2,{{1,2},{3,4}});
        EXPECT_EQ(matrix1*matrix2==matrix2,1);
    }

    TEST(utest, transpose){
        matrix<double> matrix1(2,2,{{1,2},{3,4}});
        matrix<double> matrix2(2,2,{{1,3},{2,4}});
        EXPECT_EQ(matrix1.transpose()==matrix2, 1);
    }

    TEST(utest, sym){
        matrix<double> matrix1(2,2,{{1,3},{3,4}});
        EXPECT_EQ((matrix1.is_symmetric()), 1);
    }

    TEST(utest, not_sym){
        matrix<double> matrix1(2,2,{{1,2},{3,4}});
        EXPECT_EQ((matrix1.is_symmetric()), 0);
    }

    TEST(utest, read_matrix){
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_100.txt");
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

    TEST(utest, cholesky_for_each_large) {
        matrix<double> matrix1 = create_matrix<double>("/Users/silvia/CLionProjects/tfg/my_inputs/CSR_100.txt");
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