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
project (SocketsAndTerminal)

add_executable(lexer-socket       ${CMAKE_CURRENT_SOURCE_DIR}/lexer-socket.c       ${CMAKE_CURRENT_SOURCE_DIR}/lex_ascii/Lexer.c)
add_executable(lexer-stdin        ${CMAKE_CURRENT_SOURCE_DIR}/lexer-stdin.c        ${CMAKE_CURRENT_SOURCE_DIR}/lex_ascii/Lexer.c)
add_executable(lexer-command-line ${CMAKE_CURRENT_SOURCE_DIR}/lexer-command-line.c ${CMAKE_CURRENT_SOURCE_DIR}/lex_ascii/Lexer.c)
add_executable(feed-socket        ${CMAKE_CURRENT_SOURCE_DIR}/feed-socket.c)
                                     
add_executable(lexer-socket-utf8       ${CMAKE_CURRENT_SOURCE_DIR}/lexer-socket.c       ${CMAKE_CURRENT_SOURCE_DIR}/lex_utf8/Lexer.c)
add_executable(lexer-stdin-utf8        ${CMAKE_CURRENT_SOURCE_DIR}/lexer-stdin.c        ${CMAKE_CURRENT_SOURCE_DIR}/lex_utf8/Lexer.c)
add_executable(lexer-command-line-utf8 ${CMAKE_CURRENT_SOURCE_DIR}/lexer-command-line.c ${CMAKE_CURRENT_SOURCE_DIR}/lex_utf8/Lexer.c)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(lexer-socket-utf8       PRIVATE -DWITH_UTF8)
target_compile_options(lexer-stdin-utf8        PRIVATE -DWITH_UTF8)
target_compile_options(lexer-command-line-utf8 PRIVATE -DWITH_UTF8)
          
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/lex_utf8/Lexer.c
	COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/utf8.qx -o Lexer --bet wchar_t 
            --odir ${CMAKE_CURRENT_SOURCE_DIR}/lex_utf8 --language C
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/utf8.qx)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/lex_ascii/Lexer.c
	COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/ascii.qx -o Lexer 
            --odir ${CMAKE_CURRENT_SOURCE_DIR}/lex_ascii --language C
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ascii.qx)

