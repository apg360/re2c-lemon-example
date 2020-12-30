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
project (LexerForC)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(lexer lexer.cpp ${CMAKE_CURRENT_BINARY_DIR}/lexical_analysis/LexerForC.cpp)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/lexical_analysis/LexerForC.cpp
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/c.qx -o LexerForC --odir ${CMAKE_CURRENT_BINARY_DIR}/lexical_analysis 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/c.qx 
)

