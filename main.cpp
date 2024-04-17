#include "dolittle.cpp"

int main() {
    // Cholesky
    /*matrix<double> matrix1(3, 3,
                           {{25, 15, -5},
                            {15, 18, 0},
                            {-5, 0, 11}});
    print_cholesky_factor(matrix1);
    std::cout << "Transpose:\n";
    print(std::cout, cholesky_factor(matrix1).transpose());
    std::cout << "Correct: " << check_cholesky(matrix1, cholesky_factor(matrix1)) << "\n";*/

    matrix M = read_matrix<int>("/Users/silvia/CLionProjects/linalg_seq/inputs_modified/d750.O");
    matrix Mt = cholesky_factor(M);
    matrix M2 = Mt * Mt.transpose();
    /*for(size_t i = 0; i < M.rows(); i++){
        for(size_t j = 0; j < M.rows(); j++){
            if(M(i,j) != M2(i,j)){
                std::cout << "Row: " << i << " Column: " << j << " Value M: " << M(i,j) << " Value M2: " << M2(i,j) << "\n";
            }
        }
    }*/
    std::cout << "Correct: " << (M == M2) << "\n";

    return 0;
}