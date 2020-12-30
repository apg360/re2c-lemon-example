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
project (ModesAndStuff)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(lexer  lexer.c Easy/Easy.c)
add_executable(lexer2 lexer.c Easy2/Easy2.c)
target_compile_definitions(lexer2 PRIVATE LEXER2)

set(S ${CMAKE_CURRENT_SOURCE_DIR})
set(COMMON_QX ${S}/patterns.qx ${S}/tokens.qx ${S}/common.qx)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/Easy/Easy.c
    COMMAND quex -i ${COMMON_QX} ${S}/easy.qx -o Easy --language C
    DEPENDS ${COMMON_QX} ${S}/easy.qx
)
add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/Easy2/Easy2.c
    COMMAND quex -i ${COMMON_QX} ${S}/easy2.qx -o Easy2 --language C
    DEPENDS ${COMMON_QX} ${S}/easy2.qx
)

