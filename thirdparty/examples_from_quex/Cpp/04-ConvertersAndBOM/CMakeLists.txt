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
project (ConvertersAndBom)

set(S                   ${CMAKE_CURRENT_SOURCE_DIR})
set(QX_FILES            ${S}/definitions.qx ${S}/end_of_file.qx ${S}/program.qx)
set(CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} -ggdb -pedantic -Wconversion -Wall -Werror -W")
set(BYTES_PER_CHARACTER 2)

find_package(ICU COMPONENTS uc)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(lexer          lexer.cpp          Easy/Easy.cpp)
add_executable(lexer-icu      lexer-icu.cpp      Easy/Easy.cpp)
add_executable(lexer-with-bom lexer-with-bom.cpp Easy/Easy.cpp)

target_link_libraries(lexer-icu ${ICU_LIBRARIES})

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/Easy/Easy.cpp
    COMMAND quex -i ${QX_FILES} -b ${BYTES_PER_CHARACTER} -o Easy 
    DEPENDS ${QX_FILES}
)
