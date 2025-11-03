cmake_minimum_required(VERSION 3.25)
project(FinalProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(FinalProject main.cpp extra/WireFrame.h extra/WireFrame.cpp resources/resource.h resources/resource.rc extra/gameWindowBuffer.cpp)
