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
project (WithBisonParser)

add_executable(parser main.c 
               ${CMAKE_CURRENT_SOURCE_DIR}/lexical_analysis/Calc_lexer.c 
               ${CMAKE_CURRENT_SOURCE_DIR}/Calc_parser.tab.c)
target_include_directories(parser PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(parser PRIVATE -Wno-sign-conversion -Wno-conversion)
target_link_libraries(parser PRIVATE m)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/lexical_analysis/Calc_lexer.c
    COMMAND quex -i                 ${CMAKE_CURRENT_SOURCE_DIR}/Calc_lexer.qx 
            -o                      Calc_lexer 
            --token-id-prefix       TKN_ 
            --foreign-token-id-file ${CMAKE_CURRENT_SOURCE_DIR}/Calc_token-ids.h  
		    --odir                  ${CMAKE_CURRENT_SOURCE_DIR}/lexical_analysis 
            --suppress 0            --language C         
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Calc_lexer.qx)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/Calc_parser.tab.c
    COMMAND bison ${CMAKE_CURRENT_SOURCE_DIR}/Calc_parser.y --file-prefix=../Calc_parser
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Calc_parser.y)
