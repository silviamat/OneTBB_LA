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

void ParseIntFormat(char *buf, long *num, long *size)
{
    char *tmp;
    tmp = buf;

    while (*tmp++ != '(')
        ;
    sscanf(tmp, "%ld", num);

    while (*tmp++ != 'I')
        ;
    sscanf(tmp, "%ld", size);
}

template <typename scalar_type>
matrix<scalar_type> read_input(const char *inputfile) {
    std::ifstream file;
    char buf[100], c;
    char * pEnd;
    long n, m, i, item;
    long n_rows, tmp;
    long numer_lines;
    long colnum, colsize, rownum, rowsize;

    file.open(inputfile, std::ifstream::in);
    if (!file) {
        std::cerr << "Error: Cannot open " << inputfile << " for reading\n";
    }
    // discard??
    file.read(buf, 80 * sizeof(char));
    // dumpLine
    file.read(&c, sizeof(char));
    while (c != '\n'){
        file.read(&c, sizeof(char));
    }

    for (int j=0; j<5; j++) {
        file.read(buf, 14*sizeof(char));
        sscanf(buf, "%ld", &tmp);
        if (j == 3)
            numer_lines = tmp;
    }
    // dumpLine
    file.read(&c, sizeof(char));
    while (c != '\n'){
        file.read(&c, sizeof(char));
    }
    // discard type
    file.read(buf, 14*sizeof(char));

    file.read(buf, 14*sizeof(char));
    n = strtol(buf,&pEnd, 10);
    file.read(buf, 14*sizeof(char));
    m = strtol(buf,&pEnd, 10);
    file.read(buf, 14*sizeof(char));
    n_rows = strtol(buf,&pEnd, 10);
    file.read(buf, 14*sizeof(char));
    tmp = strtol(buf,&pEnd, 10);
    if (tmp != 0){
        std::cerr << "Error: this is not an assembled matrix\n";
    }
    if (m != n){
        std::cerr << "Error: this is not a symmetric matrix\n";
    }
    // dumpLine
    file.read(&c, sizeof(char));
    while (c != '\n'){
        file.read(&c, sizeof(char));
    }

    file.read(buf, 16*sizeof(char));
    ParseIntFormat(buf, &colnum, &colsize);
    file.read(buf, 16*sizeof(char));
    ParseIntFormat(buf, &rownum, &rowsize);
    file.read(buf, 40*sizeof(char));
    // dumpLine
    file.read(&c, sizeof(char));
    while (c != '\n'){
        file.read(&c, sizeof(char));
    }

    matrix M = matrix(n, m, 0);

    // ReadVector(fp, n+1, M.col, colnum, colsize);
    i = 0;
    while (i < n) {
        file.read(buf, 100*sizeof(char));    /* read a line at a time */
        for (int j=0; j<colnum && i<n; j++) {
            tmp = buf[(j+1)*colsize]; buf[(j+1)*colsize] = 0;  /* null terminate */
            item = atoi(&buf[j*colsize]);
            buf[(j+1)*colsize] = tmp;
            M(j,i++) = item-1;
        }
    }
    //ReadVector(fp, m, M.row, rownum, rowsize);
    i = 0;
    while (i < n) {
        file.read(buf, 100*sizeof(char));    /* read a line at a time */
        for (int j=0; j<rownum && i<n; j++) {
            tmp = buf[(j+1)*rowsize]; buf[(j+1)*rowsize] = 0;  /* null terminate */
            item = atoi(&buf[j*rowsize]);
            buf[(j+1)*rowsize] = tmp;
            M(j,i++) = item-1;
        }
    }

    for (i=0; i<numer_lines; i++){ /* dump numeric values */
        // dumpLine
        file.read(&c, sizeof(char));
        while (c != '\n'){
            file.read(&c, sizeof(char));
        }
    }

    return M;
}