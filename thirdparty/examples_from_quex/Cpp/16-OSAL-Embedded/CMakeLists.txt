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
project (OsalEmbedded)

include_directories("${CMAKE_CURRENT_BINARY_DIR}" osal/build/inc osal/src/os/inc)

add_executable(lexer tiny/tiny.cpp auxiliary.cpp main.cpp tasks.cpp)
target_compile_options(lexer PUBLIC -Wall -Werror -Wno-int-to-pointer-cast)
target_link_libraries(lexer libOsalTiny -lpthread -lrt -ldl)

add_library(libOsalTiny
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osfileapi.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osfilesys.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osapi.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osloader.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osnetwork.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/ostimer.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/bsp/pc-linux/src/bsp_start.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/bsp/pc-linux/src/bsp_voltab.c)

target_compile_options(libOsalTiny PRIVATE -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast)

add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osfileapi.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osfilesys.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osapi.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osloader.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/osnetwork.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/os/posix/ostimer.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/bsp/pc-linux/src/bsp_start.c
            ${CMAKE_CURRENT_SOURCE_DIR}/osal/src/bsp/pc-linux/src/bsp_voltab.c
    COMMAND 7z x -y ${CMAKE_CURRENT_SOURCE_DIR}/../../C/16-OSAL-Embedded/osal-mini.7z -o${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command (
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/tiny/tiny.cpp
	COMMAND quex -i ${CMAKE_CURRENT_SOURCE_DIR}/tiny.qx -o tiny --tiny-stdlib --debug-original-paths
    DEPENDS tiny.qx
)

