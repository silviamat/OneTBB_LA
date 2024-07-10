#include "matrix/cholesky_opt.cpp"
#include <chrono>

using namespace std::chrono;

int main(int argc, char* argv[]) {
    matrix M = create_matrix<double>(argv[1]);
    auto start = high_resolution_clock::now();
    matrix Mt1 = cholesky_factor(M);
    auto end = high_resolution_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Sequential\nTime: " << time_elapsed << " milliseconds\n";
    start = high_resolution_clock::now();
    matrix Mt2 = cholesky_factor_for(M);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "For\nTime: " << time_elapsed << " milliseconds\n";
    start = high_resolution_clock::now();
    matrix Mt3 = cholesky_factor_reduce(M);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Reduce\nTime: " << time_elapsed << " milliseconds\n";
    start = high_resolution_clock::now();
    matrix Mt4 = cholesky_factor_for(M);
    end = high_resolution_clock::now();
    time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "For_each\nTime: " << time_elapsed << " milliseconds\n";

    return 0;
}