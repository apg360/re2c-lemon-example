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
project (Include)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(lexer-1 approach-1.c ${CMAKE_CURRENT_SOURCE_DIR}/approach-1/Easy.c)
add_executable(lexer-2 approach-2.c ${CMAKE_CURRENT_SOURCE_DIR}/approach-2/Easy.c)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/approach-1/Easy.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/approach-1.qx -o Easy --odir ${CMAKE_CURRENT_SOURCE_DIR}/approach-1 --language C
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/approach-1.qx 
)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/approach-2/Easy.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/approach-2.qx -o Easy --odir ${CMAKE_CURRENT_SOURCE_DIR}/approach-2 --language C
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/approach-2.qx 
)

