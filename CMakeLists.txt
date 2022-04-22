cmake_minimum_required(VERSION 3.22)
project(List_Container)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(List_Container main.cpp LIST.H)
