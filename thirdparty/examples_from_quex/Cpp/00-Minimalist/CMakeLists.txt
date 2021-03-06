# Build Instructions for Quex generated lexer.
#
# PURPOSE: Provide bases for a variety of build system descriptions.
#
# For example 'cmake -G "Visual Studio 14 2015 ARM"' generates code for 
# Microsofts (tm) VisualStudio IDE for ARM CPUs. The according generator must
# be installed.
#______________________________________________________________________________
#
# Execute the following commands:
#
#   > mkdir ./build
#   > cd ./build
#   > cmake ..
#   > make 
#
# Run lexer with
#
#   > cd ..
#   > ./build/lexer
#
# (C) 2018 Frank-Rene Schaefer
#______________________________________________________________________________
cmake_minimum_required (VERSION 2.6)
project (Minimalist)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(lexer lexer.cpp tiny/tiny.cpp)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/tiny/tiny.cpp
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/tiny.qx -o tiny --odir tiny 
    DEPENDS tiny.qx
)

