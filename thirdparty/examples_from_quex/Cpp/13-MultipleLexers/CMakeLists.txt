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
project (MultipleLexers)

add_executable(lexer lexer.cpp max/max.cpp moritz/moritz.cpp boeck/boeck.cpp)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/boeck")
	 
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/max/max.cpp
	COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/token.qx ${CMAKE_CURRENT_SOURCE_DIR}/max.qx 
	             -o lexer::max -b 4 
	             --token-id-prefix MAX_TKN_ --suppress 6 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/max
	             --no-lib-quex
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/max.qx)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/moritz/moritz.cpp
	COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/token.qx ${CMAKE_CURRENT_SOURCE_DIR}/moritz.qx  
	             -o lexer::moritz -b 2 
		         --token-id-prefix MORITZ_TKN_ --suppress 6 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/moritz
				 --no-lib-quex
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/moritz.qx)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/boeck/boeck.cpp
	COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/token.qx ${CMAKE_CURRENT_SOURCE_DIR}/boeck.qx 
	             -o lexer::boeck --encoding utf8 
                 --odir ${CMAKE_CURRENT_SOURCE_DIR}/boeck
		         --token-id-prefix TKN_ --suppress 6 
		         # for once: lib-quex
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/boeck.qx)

