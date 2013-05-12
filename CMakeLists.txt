cmake_minimum_required(VERSION 2.6)

project(skeletor)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
set(libraries ${SDL_LIBRARY} ${OPENGL_LIBRARY})
set(bullet_libraries BulletDynamics BulletCollision BulletSoftBody LinearMath)

file(GLOB_RECURSE sources src/*cpp src/*c)

include_directories(src)
include_directories(inc/rapidxml-1.13)
subdirs(inc/bullet-2.81)
include_directories(inc/bullet-2.81/src)
add_executable(skeletor ${sources})
target_link_libraries(skeletor ${libraries})
target_link_libraries(skeletor ${bullet_libraries})

# tests
ENABLE_TESTING()
include_directories(.)
file(GLOB_RECURSE test_sources test/*cpp test/*c)
list(REMOVE_ITEM sources "${CMAKE_SOURCE_DIR}/src/main.cpp")
add_executable(test_skeletor ${sources} ${test_sources})
target_link_libraries(test_skeletor ${libraries})
target_link_libraries(test_skeletor ${bullet_libraries})

add_test("COLLADA" ${CMAKE_CURRENT_BINARY_DIR}/test_skeletor animation collada)
