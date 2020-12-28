cmake_minimum_required(VERSION 2.8)

project(lemon)
add_executable(${PROJECT_NAME} "lemon.c")

file(COPY lempar.c DESTINATION ${CMAKE_BINARY_DIR})
