#include "matrix.hpp"
#include<fstream>

template <typename scalar_type>
void print(std::ostream& out, const matrix<scalar_type>& a) {
    size_t rows = a.rows(), columns = a.columns();
    out << std::fixed << std::setprecision(5);
    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            if (column > 0)
                out << ' ';
            out << std::setw(9) << a(row, column);
        }
        out << '\n';
    }
}

template <typename scalar_type>
void lowerToFull(matrix<scalar_type> & M){
    for(size_t i = 0; i < M.rows(); i++){
        for(size_t j = i+1; j < M.rows(); j++) {
            M(i,j) = M(j,i);
        }
    }
}

template <typename scalar_type>
matrix<scalar_type> read_matrix(const char *inputfile) {
    std::ifstream file;
    long n;
    char buf[100], *pEnd;

    file.open(inputfile, std::ifstream::in);
    if (!file) {
        std::cerr << "Error: Cannot open " << inputfile << " for reading\n";
    }

    file.read(buf, sizeof(long));
    n = strtol(buf,&pEnd, 10);

    matrix M = matrix(n, n, 0);

    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j <= i; j++) {
            file.read(buf, sizeof(scalar_type));
            M(i,j) = strtol(buf, &pEnd, 10);
        }
    }
    file.close();

    lowerToFull(M);
    return M;
}