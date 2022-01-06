# CMakeList.txt : CMake project for BP, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (BP "main.c" "main.h"         "mylib.c" "mylib.h" "BPlusTree.c" "BPlusTree.h")

# TODO: Add tests and install targets if needed.
