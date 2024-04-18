#include "matrix/cholesky_seq.cpp"
#include <chrono>

using namespace std::chrono;

int main() {
    matrix M = read_matrix<int>("/Users/silvia/CLionProjects/tfg/inputs/d750.O");
    auto start = high_resolution_clock::now();
    matrix Mt = cholesky_factor(M);
    auto end = high_resolution_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time for 750x750 matrix: " << time_elapsed << " milliseconds\n";

    return 0;
}