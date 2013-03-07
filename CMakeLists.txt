cmake_minimum_required(VERSION 2.6)

project(skeletor)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
set(libraries ${SDL_LIBRARY} ${OPENGL_LIBRARY})

file(GLOB_RECURSE sources src/*cpp src/*c)

include_directories(src)
add_executable(skeletor ${sources})
target_link_libraries(skeletor ${libraries})
