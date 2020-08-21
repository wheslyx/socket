cmake_minimum_required(VERSION 2.8.8)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(client client.cpp rocket.cpp)
add_executable(server server.cpp rocket.cpp)