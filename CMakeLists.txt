cmake_minimum_required(VERSION 3.13)

project(cmaketest2)

add_subdirectory(Math)

add_executable(cmaketest2 main.cpp)

target_include_directories(cmaketest2 PRIVATE Math)

target_link_directories(cmaketest2 PUBLIC Math)

target_link_libraries(cmaketest2 Math)