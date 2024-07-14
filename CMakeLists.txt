cmake_minimum_required(VERSION 3.5)
project(FNN LANGUAGES CXX)
add_executable(FNN main.cpp)
target_include_directories(FNN PRIVATE ${CMAKE_SOURCE_DIR}/include)
