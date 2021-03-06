# -----------------------------------------------------
# (*) brew install re2c ninja cmake

cmake_minimum_required(VERSION 3.19)
project(mycalc VERSION 0.1.0 LANGUAGES C)

# => ${CMAKE_CURRENT_SOURCE_DIR}/build
file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.h ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)

add_executable(${CMAKE_PROJECT_NAME} src/main.c )

#Compile with no optimization and adding debug symbols
set(CMAKE_BUILD_TYPE debug)
#Compile in release mode optimized but adding debug symbols
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

#
if (MSVC)
    # warning level 4 and all warnings as errors
    #add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    #add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -Werror -Wunused-parameter)
endif()

#https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_C_KNOWN_FEATURES.html
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE c_std_11) #Compiler mode is at least C 11.

# to locate include file  #include <scanner.h>
target_include_directories(${CMAKE_PROJECT_NAME}
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
   PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" # ./build
   )

