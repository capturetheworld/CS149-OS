cmake_minimum_required(VERSION 3.13)
project(persist C)

set(CMAKE_C_STANDARD 99)

add_executable(persist memdb.c)