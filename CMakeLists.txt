cmake_minimum_required(VERSION 2.6)

project(skeletor)

file(GLOB_RECURSE sources src/*cpp src/*c)

include_directories(src)
include_directories(inc/rapidxml-1.13)
add_executable(skeletor ${sources})
