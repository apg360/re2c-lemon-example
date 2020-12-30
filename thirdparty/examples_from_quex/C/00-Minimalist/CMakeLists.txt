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

add_executable(lexer lexer.c tiny/tiny.c)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/tiny/tiny.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/tiny.qx -o tiny --odir tiny --language C 
    DEPENDS tiny.qx
)

