cmake_minimum_required(VERSION 3.10)
project(Ejercicio3 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(main src/matrizMul.c)