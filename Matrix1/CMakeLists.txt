cmake_minimum_required(VERSION 3.24)
project(Matrix1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Matrix1 App.cpp ExtendedTest.cpp Matrix.cpp ShortTest.cpp ExtendedTest.h Matrix.h ShortTest.h)
