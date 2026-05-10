cmake_minimum_required(VERSION 3.30)
project(1_sort)

set(CMAKE_CXX_STANDARD 20)

add_executable(1_sort main.cpp
        model/SorTable.cpp
        model/SorTable.h
        model/TableGenerator.cpp
        model/TableGenerator.h)
