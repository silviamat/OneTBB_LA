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

    const scalar_type& operator()(size_t row, size_t column) const {
        assert(row < rows_);
        assert(column < columns_);
        return elements_[row * columns_ + column];
    }
    scalar_type& operator()(size_t row, size_t column) {
        assert(row < rows_);
        assert(column < columns_);
        return elements_[row * columns_ + column];
    }
private:
    size_t rows_;
    size_t columns_;
    std::vector<scalar_type> elements_;
};

template <typename scalar_type>
void print(std::ostream& out, const matrix<scalar_type>& a);

#endif //LINALG_SEQ_MATRIX_HPP
