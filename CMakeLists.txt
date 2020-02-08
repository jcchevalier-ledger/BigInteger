cmake_minimum_required(VERSION 3.15)
project(Modular_operations)

set(CMAKE_CXX_STANDARD 20)

add_executable(Modular_operations main.cpp BigInteger.cpp BigInteger.h)

add_library(biginteger STATIC BigInteger.cpp)