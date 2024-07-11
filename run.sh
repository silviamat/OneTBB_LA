#!/bin/bash
echo "100x100 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/CSR_100.txt" '0'
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/CSR_100.txt" '1'
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/CSR_100.txt" '2'
echo "1000x1000 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/CSR_1000.txt" '0'
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/CSR_1000.txt" '1'
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/CSR_1000.txt" '2'