cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)

project(badcode
  VERSION 0.1.0
  LANGUAGES C
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

if(WIN32)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
else(WIN32)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
endif(WIN32)

if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/contrib/lemon.c")
  message(STATUS "Downloading dependencies: lemon.c")

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/contrib"
  )

  file(DOWNLOAD "https://www.sqlite.org/src/raw/a361b85fa230560b783006ac002a6a8bad214c3b9d7fa48980aecc2b691ddcad?at=lemon.c"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/lemon.c"
    TIMEOUT 60
    EXPECTED_HASH SHA1=c4ca97954faf79054a87e44509e7eedf48d40ead
    TLS_VERIFY ON
  )
endif(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/contrib/lemon.c")

if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/contrib/lempar.c")
  message(STATUS "Downloading dependencies: lempar.c")
  
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/contrib
  )

  file(DOWNLOAD "https://www.sqlite.org/src/raw/e8899b28488f060d0ff931539ea6311b16b22dce068c086c788a06d5e8d01ab7?at=lempar.c"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/lempar.c"
    TIMEOUT 60
    EXPECTED_HASH SHA1=91e680cccb97fcf312f210c76502595fa7dd3e32
    TLS_VERIFY ON
  )

endif(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/contrib/lempar.c")

if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c-1.3")
  message(STATUS "Downloading dependencies: re2c-1.3")

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/contrib
  )

  file(DOWNLOAD "https://github.com/skvadrik/re2c/releases/download/1.3/re2c-1.3.tar.xz"
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c-1.3.tar.xz
    TIMEOUT 60
    EXPECTED_HASH SHA1=857d153c82000d854d33d0c2972f2743967b81b1
    TLS_VERIFY ON
  )

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c-1.3.tar.xz
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/contrib
  )
endif()

add_executable(lemon
  contrib/lemon.c
)

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c/bin/re2c"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/contrib/build"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c"
  COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_BINARY_DIR}/contrib/build" "${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c-1.3/configure" --prefix "/"
  COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_BINARY_DIR}/contrib/build" make
  COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_BINARY_DIR}/contrib/build" make DESTDIR="${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c" install
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c-1.3/configure
)

add_custom_target(re2c
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c/bin/re2c"
)

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/bcParser.c" "${CMAKE_CURRENT_BINARY_DIR}/bcParser.h" "${CMAKE_CURRENT_BINARY_DIR}/bcParser.out"
  COMMAND $<TARGET_FILE:lemon>  -T"${CMAKE_CURRENT_BINARY_DIR}/contrib/lempar.c" -d"${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/bcParser.y"
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/bcParser.y"
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/contrib/lempar.c"
  DEPENDS lemon
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/bcLexer.c"
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/contrib/re2c/bin/re2c" --utf-8 --input-encoding utf8 --output "${CMAKE_CURRENT_BINARY_DIR}/bcLexer.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/bcLexer.re"
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/bcLexer.re"
  DEPENDS re2c
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)


add_library(badsetup INTERFACE)

target_compile_options(badsetup INTERFACE
  $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -Wconversion -fdiagnostics-color=always -pedantic -Werror=implicit-function-declaration>
  $<$<C_COMPILER_ID:Clang>:-Wall -Wextra -Wconversion -fcolor-diagnostics -pedantic -Werror=implicit-function-declaration>
)

if (UNIX)
  target_link_libraries(badsetup INTERFACE
    m
  )

  target_compile_definitions(badsetup INTERFACE
    _GNU_SOURCE
  )

endif(UNIX)

if (WIN32)

  target_compile_definitions(badsetup INTERFACE
    _USE_MATH_DEFINES
    _CRT_SECURE_NO_WARNINGS
  )

  target_compile_options(badsetup INTERFACE
    /source-charset:utf-8
  )

endif(WIN32)

add_library(badcode STATIC
# PUBLIC INTERFACE
  include/badcode.h

# PRIVATE INTERFACE
  src/private/bcPrivate.h
  src/private/bcValue.h
  src/private/bcValueStack.h
  src/private/bcParseTree.h

# SOURCES
  src/badcode.c
  src/bcValue.c
  src/bcGlobal.c
  src/bcValueStack.c
  src/bcParseTree.c
  src/bcOpcode.c
  src/bcCStream.c

# GENERATED SOURCES
  "${CMAKE_CURRENT_BINARY_DIR}/bcParser.c"
  "${CMAKE_CURRENT_BINARY_DIR}/bcParser.h"
  "${CMAKE_CURRENT_BINARY_DIR}/bcLexer.c"
)

target_compile_options(badcode PUBLIC
  $<$<CONFIG:Debug>:-g3>
)

target_include_directories(badcode
  PUBLIC
    include
  PRIVATE
    src/private
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(badcode
  PUBLIC
    badsetup
)

# TESTS

add_executable(badrepl
  tests/badrepl.c
)

target_link_libraries(badrepl
  PRIVATE
    badcode
)

