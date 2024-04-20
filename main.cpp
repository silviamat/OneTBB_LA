#include "matrix/cholesky_par.cpp"
#include <chrono>

using namespace std::chrono;

int main() {
    matrix M = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/tk29.O");
    matrix cholesky = cholesky_factor(M);
    matrix transpose = cholesky.transpose();
    matrix M2 = cholesky*transpose;

    std::cout << "Correct: " << (M == M2);
    /*auto start = high_resolution_clock::now();
    matrix Mt = cholesky_factor(M);
    auto end = high_resolution_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time for 750x750 matrix: " << time_elapsed << " milliseconds\n";*/

    return 0;
}