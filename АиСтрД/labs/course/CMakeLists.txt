cmake_minimum_required(VERSION 3.14)
project(course)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE graph-data.cpp
           graph-source.cpp
           graph.cpp
           node.cpp
   )

add_executable(course main.cpp ${SOURCE})
