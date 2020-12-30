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
project (ManualBufferFilling)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(point-plain.exe        lexer-point.cpp              plain/Lexer.cpp)
target_compile_options(point-plain.exe  PRIVATE -DQUEX_SETTING_BUFFER_SIZE_EXT=13)

add_executable(feeder-plain.exe       lexer-feeder.cpp receiver.cpp  plain/Lexer.cpp)
add_executable(gavager-plain.exe      lexer-gavager.cpp receiver.cpp plain/Lexer.cpp)
target_compile_options(feeder-plain.exe  PRIVATE -DQUEX_SETTING_BUFFER_SIZE_EXT=13)
target_compile_options(gavager-plain.exe PRIVATE -DQUEX_SETTING_BUFFER_SIZE_EXT=13)

add_executable(feeder-converter.exe   lexer-feeder.cpp receiver.cpp  converter/Lexer.cpp)
add_executable(gavager-converter.exe  lexer-gavager.cpp receiver.cpp converter/Lexer.cpp)
target_compile_options(feeder-converter.exe PRIVATE
                       -DQUEX_SETTING_BUFFER_LEXATOM_LOADER_CONVERTER_BUFFER_SIZE_EXT=6 
	                   -DQUEX_SETTING_BUFFER_SIZE_EXT=16            
			           -DQUEX_TYPE_LEXATOM_EXT=wchar_t              
			           -DQUEX_DEMO_WITH_CONVERTER                   
			           -DQUEX_DEMO_OPTION_CONVERTER_ICONV)
target_compile_options(gavager-converter.exe PRIVATE
                       -DQUEX_SETTING_BUFFER_LEXATOM_LOADER_CONVERTER_BUFFER_SIZE_EXT=6 
	                   -DQUEX_SETTING_BUFFER_SIZE_EXT=16            
			           -DQUEX_TYPE_LEXATOM_EXT=wchar_t              
			           -DQUEX_DEMO_WITH_CONVERTER                   
			           -DQUEX_DEMO_OPTION_CONVERTER_ICONV)
          
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/plain/Lexer.cpp
	COMMAND quex --cbm --fallback-mandatory 
		 -i ${CMAKE_CURRENT_SOURCE_DIR}/lexPlain.qx -o Lexer 
	     --odir ${CMAKE_CURRENT_SOURCE_DIR}/plain 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexPlain.qx)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/converter/Lexer.cpp
	COMMAND quex --cbm --fallback-mandatory 
	     -i ${CMAKE_CURRENT_SOURCE_DIR}/lexConverter.qx -o Lexer 
	     --odir ${CMAKE_CURRENT_SOURCE_DIR}/converter 
		 --buffer-element-type wchar_t 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexConverter.qx)
