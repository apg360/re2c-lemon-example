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
project (EngineEncoding)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(iso8859-7-lexer iso8859-7-lexer.cpp iso8859-7/ISO8859_7_Lex.cpp)
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/iso8859-7/ISO8859_7_Lex.cpp
	COMMAND quex -i           ${CMAKE_CURRENT_SOURCE_DIR}/greek.qx  
			--encoding        iso8859_7 
			--token-id-prefix TKN_      
			-o                ISO8859_7_Lex 
			--odir            ${CMAKE_CURRENT_SOURCE_DIR}/iso8859-7 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/greek.qx)

add_executable(utf8-lexer utf8-lexer.cpp utf8/UTF8Lex.cpp)
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/utf8/UTF8Lex.cpp
	COMMAND quex -i            ${CMAKE_CURRENT_SOURCE_DIR}/greek.qx            
			 --encoding        utf8        
			 --token-id-prefix TKN_ 
			 -o                UTF8Lex             
			 --odir            ${CMAKE_CURRENT_SOURCE_DIR}/utf8 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/greek.qx)
	
add_executable(utf16-lexer utf16-lexer.cpp utf16/UTF16Lex.cpp)
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/utf16/UTF16Lex.cpp
	COMMAND quex -i           ${CMAKE_CURRENT_SOURCE_DIR}/greek.qx  
		    --encoding        utf16     
		    --token-id-prefix TKN_      
	        -b                2         
		    -o                UTF16Lex  
			--odir            ${CMAKE_CURRENT_SOURCE_DIR}/utf16 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/greek.qx)

add_executable(utf16-lexer-other utf16-lexer-other.cpp utf16-other/UTF16Lex.cpp)
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/utf16-other/UTF16Lex.cpp
    COMMAND quex -i           ${CMAKE_CURRENT_SOURCE_DIR}/greek-other.qx  
		    --encoding        utf16           
		    --token-id-prefix TKN_            
	        -b                2               
		    -o                UTF16Lex 
			--odir            ${CMAKE_CURRENT_SOURCE_DIR}/utf16-other 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/greek.qx)

