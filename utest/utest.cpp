#include "matrix/cholesky_seq.cpp"
#include <gtest/gtest.h>

namespace {
    TEST(utest, cholesky_seq) {
        // we test all block.cpp functionalities for the small file and traces
        matrix<double> matrix1(3, 3,
                               {{25, 15, -5},
                                {15, 18, 0},
                                {-5, 0,  11}});
        matrix cholesky = cholesky_factor(matrix1);
        matrix transpose = cholesky.transpose();
        matrix matrix2 = cholesky * transpose;
        EXPECT_EQ((matrix1 == matrix2), 1);
    }
}