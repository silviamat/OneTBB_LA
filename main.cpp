#include "matrix/dolittle_opt.cpp"
#include <chrono>

using namespace std::chrono;

int main(int argc, char* argv[]) {
    matrix M = read_matrix<int>(argv[1]);
    auto start = high_resolution_clock::now();
    if(argv[2] == nullptr){
        matrix Mt = cholesky_factor(M);
    }else{
        matrix Mt = cholesky_factor_opt(M);
    }
    auto end = high_resolution_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Time: " << time_elapsed << " milliseconds\n";

    return 0;
}