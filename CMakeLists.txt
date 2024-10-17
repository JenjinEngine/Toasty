cmake_minimum_required(VERSION 3.5)

# Build type
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ configs
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Project declaration
project(ImDecoratedRoot)

add_subdirectory(./ImDecorated/vendor)

add_subdirectory(toasty)
add_subdirectory(ImDecorated/imdecorated)
add_subdirectory(test)

