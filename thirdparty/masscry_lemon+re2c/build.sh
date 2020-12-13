#!/usr/bin/env sh

# Makes separate build directory and runs cmake to build project in it

cmake -E make_directory ./.debug
cd .debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang ../
cmake --build ./ -- -j4