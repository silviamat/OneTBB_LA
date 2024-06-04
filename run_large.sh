#!/bin/bash
echo "Sequential:"
echo "750x750 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/d750.O"
echo "1806x1806 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/tk14.O"
echo "4884x4884 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/tk16.O"

echo "Parallel:"
echo "750x750 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/d750.O" 1
echo "1806x1806 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/tk14.O" 1
echo "4884x4884 matrix"
./cmake-build-debug/tfg "/Users/silvia/CLionProjects/tfg/my_inputs/tk16.O" 1