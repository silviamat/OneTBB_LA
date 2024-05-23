add_library(matrix
        matrix.hpp
        matrix.cpp
        dolittle_seq.cpp
        cholesky_seq.cpp
        cholesky_opt.cpp
        dolittle_opt.cpp
)

find_package(TBB)
target_link_libraries(matrix TBB::tbb)