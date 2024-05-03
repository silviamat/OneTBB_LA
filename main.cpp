#include "matrix/cholesky_opt.cpp"
#include <chrono>

using namespace std::chrono;

int main() {
    matrix M = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/d750.O");
    auto start = high_resolution_clock::now();
    matrix Mt = cholesky_factor(M);
    auto end = high_resolution_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Sequential:\nTime for 750x750 matrix: " << time_elapsed << " milliseconds\n";

    matrix M2 = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/tk14.O");
    start = high_resolution_clock::now();
    matrix Mt2 = cholesky_factor(M2);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time for 1806x1806 matrix: " << time_elapsed << " milliseconds\n";

    /*matrix M3 = read_matrix<int>("/Users/silvia/CLionProjects/tfg/my_inputs/tk16.O");
    start = high_resolution_clock::now();
    matrix Mt3 = cholesky_factor(M3);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time for 4884x4884 matrix: " << time_elapsed << " milliseconds\n";*/

    start = high_resolution_clock::now();
    Mt = cholesky_factor_opt(M);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Parallel:\nTime for 750x750 matrix: " << time_elapsed << " milliseconds\n";

    start = high_resolution_clock::now();
    Mt2 = cholesky_factor_opt(M2);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time for 1806x1806 matrix: " << time_elapsed << " milliseconds\n";

    /*start = high_resolution_clock::now();
    Mt3 = cholesky_factor_opt(M3);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time for 4884x4884 matrix: " << time_elapsed << " milliseconds\n";*/

    return 0;
}