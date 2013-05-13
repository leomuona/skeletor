cmake_minimum_required(VERSION 2.6)

project(skeletor)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
set(libraries ${SDL_LIBRARY} ${OPENGL_LIBRARY})
set(bullet_libraries BulletDynamics BulletCollision BulletSoftBody LinearMath)

file(GLOB_RECURSE lib_sources src/*cpp src/*c)
list(REMOVE_ITEM lib_sources "${CMAKE_SOURCE_DIR}/src/main.cpp")

include_directories(src)
include_directories(inc/rapidxml-1.13)
subdirs(inc/bullet-2.81)
include_directories(inc/bullet-2.81/src)

add_library(lib_skeletor ${lib_sources})
target_link_libraries(lib_skeletor ${libraries})
target_link_libraries(lib_skeletor ${bullet_libraries})

add_executable(skeletor "${CMAKE_SOURCE_DIR}/src/main.cpp")
target_link_libraries(skeletor lib_skeletor)

# tests
ENABLE_TESTING()
include_directories(.)
file(GLOB_RECURSE test_sources test/*cpp test/*c)
add_executable(test_skeletor ${test_sources})
target_link_libraries(test_skeletor lib_skeletor)

add_test("COLLADA" ${CMAKE_CURRENT_BINARY_DIR}/test_skeletor animation collada)
add_test("KeyFrame" ${CMAKE_CURRENT_BINARY_DIR}/test_skeletor animation keyframe)
add_test("PlayerMovement" ${CMAKE_CURRENT_BINARY_DIR}/test_skeletor player_movement)
