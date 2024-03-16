cmake_minimum_required(VERSION 3.14)
project(cpp-interview-prep)


add_executable(task1 src/task1/main.cpp)
add_executable(task2 src/task2/main.cpp)
add_executable(task3 src/task3/main.cpp)

target_compile_features(task1 PRIVATE cxx_std_20)