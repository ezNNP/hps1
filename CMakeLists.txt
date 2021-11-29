cmake_minimum_required(VERSION 3.16)
project(L1 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

add_executable(L1 main.c smooth_sort.c smooth_sort.h quick_sort.c quick_sort.h array_utils.c array_utils.h test_utils.c test_utils.h)
