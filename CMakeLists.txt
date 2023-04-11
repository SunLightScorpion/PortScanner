cmake_minimum_required(VERSION 3.25)
project(PortScanner)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        PortScanner
        src/core.cpp
)
