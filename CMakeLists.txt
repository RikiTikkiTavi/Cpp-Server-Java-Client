cmake_minimum_required(VERSION 3.10)
project(cppServer)

set(CMAKE_CXX_STANDARD 17)
add_definitions("-lpthread")
find_package (Threads)
add_executable(cppServer server.cpp)
add_executable(cppClient client.cpp)
target_link_libraries (cppServer ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (cppClient ${CMAKE_THREAD_LIBS_INIT})