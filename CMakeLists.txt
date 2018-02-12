cmake_minimum_required(VERSION 3.9)
project(hw2 C)

set(CMAKE_C_STANDARD 99)

add_executable(hw2 threads.c mysh.c Lab01Part1.c TestingExecvp.c)