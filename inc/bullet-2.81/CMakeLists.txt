cmake_minimum_required(VERSION 2.6)

project(BULLET_PHYSICS)
set(BULLET_VERSION 2.81)
if (NOT CMAKE_BUILD_TYPE)
        SET(CMAKE_BUILD_TYPE "Release")
endif (NOT CMAKE_BUILD_TYPE)

SUBDIRS( src/BulletSoftBody src/BulletCollision src/BulletDynamics src/LinearMath )
