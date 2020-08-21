cmake_minimum_required(VERSION 2.8.8)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

#add_executable(client_data client_data.cpp Socket.cpp)
#add_executable(server_data server_data.cpp Socket.cpp)
add_executable(server server_data.cpp)
add_executable(client client_data.cpp)