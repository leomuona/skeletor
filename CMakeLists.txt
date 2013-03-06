cmake_minimum_required(VERSION 2.6)

project(skeletor)

file(GLOB_RECURSE sources src/*cpp src/*c)

add_executable(skeletor ${sources})
