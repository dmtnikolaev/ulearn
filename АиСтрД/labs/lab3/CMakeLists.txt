cmake_minimum_required(VERSION 3.14)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE tree.cpp
           screen.cpp
    )
set(HEADER node.h
           tree.h
           screen.h
    )
    
add_executable(lab3 lab3.cpp ${SOURCE})
