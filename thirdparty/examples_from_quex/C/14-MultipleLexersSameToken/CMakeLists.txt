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

add_executable(lexer lexer.c max/max_Lexer.c moritz/moritz_Lexer.c boeck/boeck_Lexer.c ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.c)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}" 
                    "${CMAKE_CURRENT_SOURCE_DIR}/boeck"
                    "${CMAKE_CURRENT_SOURCE_DIR}/A_B_C")
target_link_libraries(lexer ${ICU_LIBRARIES})

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/max/max.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/max.qx -o max_Lexer 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/max -b 4 
                 --token-id-prefix  MAX_TKN_ 
                 --token-class-file ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.h 
                 --suppress         0 1 6 
                 --no-lib-quex 
                 --language C 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/max.qx
            ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.c)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/moritz/moritz.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/moritz.qx -o moritz_Lexer 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/moritz -b 4 
                 --token-id-prefix  MORITZ_TKN_ 
                 --token-class-file ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.h 
                 --suppress         0 1 6 
                 --no-lib-quex 
                 --language C 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/moritz.qx
            ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.c)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/boeck/boeck.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/boeck.qx -o boeck_Lexer 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/boeck -b 4 
                 --token-id-prefix  TKN_ 
                 --token-class-file ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.h 
                 --suppress         0 1 6 
                 --no-lib-quex 
                 --language C 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/boeck.qx
            ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.c)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C/Global-token.c
    COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/token_ids.qx 
		    --odir ${CMAKE_CURRENT_SOURCE_DIR}/A_B_C -b 4  
            --token-class-only -o Global --token-class Common_Token 
            --language C  
		    # generate lib-quex
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/token_ids.qx)
