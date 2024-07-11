#include "matrix/cholesky_opt.cpp"
#include <chrono>

using namespace std::chrono;

int main(int argc, char* argv[]) {
    matrix<double> M = create_matrix<double>(argv[1]);
    int type = strtol(argv[2],nullptr,0);
    auto start = high_resolution_clock::now();
    if(type == 0){
        matrix Mt1 = cholesky_factor(M);
    }else if(type == 1){
        matrix Mt2 = cholesky_factor_reduce(M);
    }else{
        matrix Mt3 = cholesky_factor_for_each(M);
    }
    auto end = high_resolution_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    if(type == 0){
        std::cout << "Sequential\nTime: " << time_elapsed << " milliseconds\n";
    }else if(type == 1){
        std::cout << "Parallel reduce\nTime: " << time_elapsed << " milliseconds\n";
    }else{
        std::cout << "Parallel for each\nTime: " << time_elapsed << " milliseconds\n";
    }

    return 0;
}