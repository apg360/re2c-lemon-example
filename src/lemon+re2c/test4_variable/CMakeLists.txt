# -----------------------------------------------------
# (*) MacOS : brew install re2c ninja cmake

cmake_minimum_required(VERSION 3.19)
project(mycalc VERSION 0.1.0 LANGUAGES C)

# CURRENT_BINARY_DIR = CURRENT_SOURCE_DIR/build
file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.h ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)
file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.h ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.c ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.out ${CMAKE_CURRENT_BINARY_DIR}/parser.out)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${CMAKE_PROJECT_NAME} src/main.c build/parser.c)

#Compile with no optimization and adding debug symbols
set(CMAKE_BUILD_TYPE debug)
#Compile in release mode optimized but adding debug symbols
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

#Flags to enforce best practices code programming
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    #add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors -Wunused-parameter -Wunused-value -Wmacro-redefined -Wmisleading-indentation -Wunused-comparison)
    add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
endif()

#https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_C_KNOWN_FEATURES.html
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE c_std_11) #Compiler mode is at least C 11.

#Add library libm : Finding and linking libm
if(APPLE)
  find_library(MATH_LIBRARY NAMES libm.dylib)
elseif(UNIX)
  find_library(MATH_LIBRARY NAMES libm.a)
endif()
if(MATH_LIBRARY)
  get_filename_component(MATH_LIB_DIR ${MATH_LIBRARY} PATH)
  link_directories(${MATH_LIB_DIR})
  message(STATUS "libm FOUND ${MATH_LIBRARY}")
  
  # Name the library both with a full path and as "-lm" to
  # activate the link type switching code for both cases.
  # If the second one links shared then the link will fail.
  #set(MATH_LIBRARIES ${MATH_LIBRARY} -lm)
  
  set(MATH_LIBRARIES -lm)
  target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${MATH_LIBRARIES})
else()
  message(FATAL_ERROR "Cannot find libm.a needed for this test")
endif()

#Add library common_requirement : A library with most common needs when programming
add_library(common_requirement "include/common.h" "include/common.c")
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC common_requirement)


# to locate include file  #include <scanner.h> + #include <parser.h>
target_include_directories(${CMAKE_PROJECT_NAME}
   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
   PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" # ./build
   )

