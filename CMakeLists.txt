cmake_minimum_required(VERSION 3.10)
project(cppServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppServer server/main.cpp)
add_executable(cppClient client/main.cpp)