cmake_minimum_required(VERSION 3.31)
project(c)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(c
        passwords.cpp
        Analyse.cpp
        Analyse.h
        multiply.cpp
        multiply.h
        set.cpp
        unordered_set.h
        matrix.h
)
