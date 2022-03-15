cmake_minimum_required(VERSION 3.21)
project(project C)

set(CMAKE_C_STANDARD 11)

add_executable(project main.c)

add_library(sortFunc
        sortFunc/sortFunc.c
        sortFunc/sortFunc.h)

add_library(generatingFunc
        generatingFunc/generatingFunc.c
        generatingFunc/generatingFunc.h)

add_library(compare
        compare/compare.c
        compare/compare.h)

add_library(swap
        swap/swap.h
        swap/swap.c)

add_library(test
        test/test.c test/test.h)

target_link_libraries(test
        sortFunc
        compare
        generatingFunc
        swap)

target_link_libraries(project
        sortFunc
        generatingFunc
        compare
        swap
        test)
