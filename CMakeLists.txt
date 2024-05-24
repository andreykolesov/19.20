cmake_minimum_required(VERSION 3.26)
project(untitled11 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled11 main.c
        libs/algorithms/array/array.h
        libs/algorithms/array/array.c
        libs/algorithms/algorithm.c
        libs/algorithms/algorithm.h
        libs/data_structures/bitset/bitset.h
        libs/data_structures/bitset/bitset.c
        libs/data_structures/matrix/matrix.h
        libs/data_structures/matrix/matrix.c
        libs/data_structures/ordered_array_set/ordered_array_set.c
        libs/data_structures/string/string_.c
        libs/data_structures/unordered_array_set/unordered_array_set.c
        libs/data_structures/vector/vector.c
        libs/data_structures/vectorVoid/vectorVoid.c
        libs/algorithms/tasks/fill_matrix.h
        libs/algorithms/tasks/game_life.h
        libs/algorithms/tasks/median_filter.h
        libs/algorithms/tasks/get_domains.h
        libs/algorithms/tasks/get_submatrix.h
        libs/algorithms/tasks/generate_numbers.h
        libs/algorithms/tasks/get_binary_tree.h
        libs/algorithms/tasks/rearrange_string.h
)
