add_library(matrix
        matrix.hpp
        matrix.cpp
        dolittle.cpp
        gaussian.cpp
        cholesky_seq.cpp
        cholesky_opt.cpp)

find_package(TBB)
target_link_libraries(matrix TBB::tbb)