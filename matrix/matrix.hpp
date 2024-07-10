#ifndef LINALG_SEQ_MATRIX_HPP
#define LINALG_SEQ_MATRIX_HPP

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <cassert>

template <typename scalar_type> class matrix {
public:
    matrix(size_t rows, size_t columns)
            : rows_(rows), columns_(columns), elements_(rows * columns) {}

    matrix(size_t rows, size_t columns, scalar_type value)
            : rows_(rows), columns_(columns), elements_(rows * columns, value) {}

    matrix(size_t rows, size_t columns,
           const std::initializer_list<std::initializer_list<scalar_type>>& values)
            : rows_(rows), columns_(columns), elements_(rows * columns) {
        assert(values.size() <= rows_);
        size_t i = 0;
        for (const auto& row : values) {
            assert(row.size() <= columns_);
            std::copy(begin(row), end(row), &elements_[i]);
            i += columns_;
        }
    }

    size_t rows() const { return rows_; }
    size_t columns() const { return columns_; }
    size_t size() const { return elements_.size();}

    scalar_type& operator()(size_t row, size_t column) {
        assert(row < rows_);
        assert(column < columns_);
        return elements_[row * columns_ + column];
    }

    scalar_type& operator[](size_t elem) {
        assert(elem < elements_.size());
        return elements_[elem];
    }

    const scalar_type& operator()(size_t row, size_t column) const {
        assert(row < rows_);
        assert(column < columns_);
        return elements_[row * columns_ + column];
    }

    bool operator == (const matrix<scalar_type> other){
        if(other.rows() != rows_){return false;}
        if(other.columns() != columns_){return false;}
        for(size_t i = 0; i < rows_; i++){
            for(size_t j = 0; j < columns_ ; j++){
                if(elements_[i*columns_ + j] != other(i,j)){
                    return false;
                }
            }
        }
        return true;
    }

    matrix operator * (matrix other){
        assert(columns_ == other.rows());
        assert(rows_ > 0 && columns_ > 0 && other.columns_ > 0);
        assert(rows_ * columns_ <= elements_.size() && other.rows() * other.columns() <= other.size());
        matrix result(rows_, other.columns());
        for (unsigned int i = 0; i < rows_; i++) {
            for (unsigned int j = 0; j < other.columns(); j++) {
                scalar_type temp = elements_[i * columns_] * other(0,j);
                for (unsigned int k = 1; k < columns_; k++) {
                    temp += elements_[(i * columns_) + k] * other(k,j);
                }
                result(i,j) = temp;
            }
        }
        return result;
    }

    matrix transpose(){
        matrix result(columns_, rows_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < columns_; j++) {
                result(j,i) = elements_[i*columns_ + j];
            }
        }
        return result;
    }

    bool is_symmetric(){
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < columns_; j++) {
                if(elements_[i*columns_ + j] != elements_[j*columns_ + i]){
                    return false;
                }
            }
        }
        return true;
    }

    bool is_lower(){
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = i+1; j < columns_; j++) {
                if(elements_[i*columns_ + j] != 0){
                    return false;
                }
            }
        }
        return true;
    }

private:
    size_t rows_;
    size_t columns_;
    std::vector<scalar_type> elements_;
};

template <typename scalar_type> void print(std::ostream& out, const matrix<scalar_type>& a);
template <typename scalar_type> matrix<scalar_type> read_matrix(const char *inputfile);
//template <typename scalar_type> matrix<scalar_type> create_matrix(const char *inputfile);

#endif //LINALG_SEQ_MATRIX_HPP
