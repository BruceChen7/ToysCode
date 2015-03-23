cmake_minimum_required(VERSION 2.8)
project(TOYS_DS C)

add_subdirectory(test)

set(
    Toy_DS
    binary_tree.c
    )

add_library(DS ${Toy_DS})

enable_testing()

