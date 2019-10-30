cmake_minimum_required(VERSION 3.14)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE lab2.cpp 
            arr.cpp
            bitarr.cpp
            list.cpp
            word.cpp)
set(HEADER arr.h
            bitarr.h
            list.h
            word.h)
add_definitions(-DSET_IMPL=1)    
add_executable(lab2 lab2.cpp ${SOURCE})