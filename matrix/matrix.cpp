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
        for(size_t j = i+1; j < M.columns(); j++){
            M(j, i) = M(i, j); // Update the symmetric element
        }
    }
}

void readVector(std::ifstream & file, std::vector<long> & input, long n, long num, long size){
    long i, j, item;
    char tmp, buf[100], *pEnd;

    i = 0;
    while (i < n) {
        if(i+num + 1 > n){
            file.read(buf, (n-i)*size + 1);
        }else {
            file.read(buf, num * size + 1);
        }
        j = 0;
        while(j < num && i<n) {
            tmp = buf[(j+1)*size];
            buf[(j+1)*size] = 0;  /* null terminate */
            item = strtol(&buf[j*size], &pEnd, 10);
            buf[(j+1)*size] = tmp;
            input.push_back(item);
            i++;
            j++;
        }
    }
}

template <typename scalar_type>
void create_matrix(matrix<scalar_type> & M, std::vector<long> row, std::vector<long> col, long n){
    size_t count = 0;
    scalar_type maxm = 0;
    for(size_t i = 0; i < row.size() - 1; i++){
        if (row[i+1] - row[i] > maxm) {
            maxm = row[i+1] - row[i];
        }
    }

    for(size_t i = 0; i < row.size() - 1; i++){
        for(size_t j = 0; j < row[i+1] - row[i]; j++){
            if (col[count]-1 == (row[i] - row[i]*n)) {
                M(i,col[count]-1) = maxm + 0.1;
            } else {
                M(i,col[count]-1) = -1;
            }
            count++;
        }
    }
}

template <typename scalar_type>
matrix<scalar_type> read_matrix(const char *inputfile) {
    std::ifstream file;
    char c;
    long n, m, rowsize, rownum, colsize, colnum;
    std::vector<long> row,col;

    file.open(inputfile, std::ifstream::in);
    if (!file) {
        std::cerr << "Error: Cannot open " << inputfile << " for reading\n";
    }

    file >> n >> m >> rownum >> rowsize >> colnum >> colsize;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    matrix M = matrix(n,n,0);
    row.push_back(0);
    readVector(file, row, n, rownum, rowsize);
    readVector(file, col, m, colnum, colsize);
    create_matrix(M, row, col, n);
    lowerToFull(M);

    if(file.peek() != EOF){
        std::cerr << "Error: file was not read completely\n";;
    }
    file.close();

    return M;
}