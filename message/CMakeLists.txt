cmake_minimum_required(VERSION 3.13)
project(message C)

set(CMAKE_C_STANDARD 99)

add_executable(message server.c)
add_executable(client.c)