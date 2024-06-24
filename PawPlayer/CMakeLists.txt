cmake_minimum_required (VERSION 3.28)
SET(CMAKE_CXX_STANDARD 17)

project(PawPlayer)
include(${CMAKE_SOURCE_DIR}/CPM.cmake)
set(CPM_SOURCE_CACHE ${CMAKE_SOURCE_DIR}/Cache)

add_executable(${PROJECT_NAME} Source/PawPlayer.cpp)