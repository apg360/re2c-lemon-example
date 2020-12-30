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
# Run 'dna_statistics', 'spelling', 'vowel_tolerance' following the scheme
#
#   > cd ..
#   > ./build/dna_statistics
#
# (C) 2018 Frank-Rene Schaefer
#______________________________________________________________________________
cmake_minimum_required (VERSION 2.8)
project (FuzzyMatch)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(dna_statistics  dna.c           DnaLex/DnaLex.c)
add_executable(spelling        spelling.c        SpellLex/SpellLex.c)
add_executable(vowel_tolerance vowel_tolerance.c TolerantLex/TolerantLex.c)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/DnaLex/DnaLex.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/dna.qx -o DnaLex --odir DnaLex --language C 
    DEPENDS dna.qx
)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/SpellLex/SpellLex.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/spelling.qx -o SpellLex --odir SpellLex --language C 
    DEPENDS spelling.qx
)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/TolerantLex/TolerantLex.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/vowel_tolerance.qx -o TolerantLex --odir TolerantLex --encoding utf8 --language C 
    DEPENDS vowel_tolerance.qx
)

