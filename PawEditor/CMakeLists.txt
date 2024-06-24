cmake_minimum_required (VERSION 3.28)
SET(CMAKE_CXX_STANDARD 17)

project(PawEditor)
include(${CMAKE_SOURCE_DIR}/CPM.cmake)
set(CPM_SOURCE_CACHE ${CMAKE_SOURCE_DIR}/Cache)

add_executable(${PROJECT_NAME} Source/PawEditor.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC PawCore)

