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
project (MultipleLexersSameToken)

find_package(ICU COMPONENTS uc)

add_executable(lexer lexer.cpp max/Lexer.cpp moritz/Lexer.cpp boeck/Lexer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.cpp)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}" 
                    "${CMAKE_CURRENT_SOURCE_DIR}/boeck"
                    "${CMAKE_CURRENT_SOURCE_DIR}/A_B_C")
target_link_libraries(lexer ${ICU_LIBRARIES})

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/max/Lexer.cpp
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/max.qx -o max::Lexer 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/max -b 4 
                 --token-id-prefix  MAX_TKN_ 
                 --token-class-file ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token
                 --suppress         0 1 6 
                 --no-lib-quex 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/max.qx
            ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.cpp)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/moritz/Lexer.cpp
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/moritz.qx -o moritz::Lexer 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/moritz -b 4 
                 --token-id-prefix  MORITZ_TKN_ 
                 --token-class-file ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token 
                 --suppress         0 1 6 
                 --no-lib-quex 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/moritz.qx
            ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.cpp)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/boeck/Lexer.cpp
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/boeck.qx -o boeck::Lexer 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/boeck -b 4 
                 --token-id-prefix  TKN_ 
                 --token-class-file ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token 
                 --suppress         0 1 6 
                 --no-lib-quex 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/boeck.qx
            ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.cpp)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.cpp
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/token_ids.qx 
		    --odir ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C -b 4  
            --token-class-only -o Global --token-class Common::Token 
		    # generate lib-quex
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/token_ids.qx)
