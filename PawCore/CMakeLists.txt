cmake_minimum_required(VERSION 3.28)
SET(CMAKE_CXX_STANDARD 17)

project(PawCore)
include(${CMAKE_SOURCE_DIR}/CPM.cmake)
set(CPM_SOURCE_CACHE ${CMAKE_SOURCE_DIR}/Cache)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SDL_STATIC ON)


CPMAddPackage(
        NAME SDL
        GITHUB_REPOSITORY
        thatcosmonaut/SDL
        GIT_TAG gpu)

CPMAddPackage(
        NAME Flecs
        GITHUB_REPOSITORY SanderMertens/flecs
        GIT_TAG master)

CPMAddPackage(
        NAME spdlog
        GITHUB_REPOSITORY gabime/spdlog
        GIT_TAG v1.x
)

add_library(
        ${PROJECT_NAME}
        Public/PawCore.hpp
        Public/ExportAPI.hpp
        Public/Renderer/Renderer.hpp
        Public/Renderer/Renderer.cpp
        Public/Types.hpp
        Public/Config/RendererConfig.hpp
        Public/Logging.hpp
        Public/Context/Context.hpp
        Public/Context/Context.cpp
        Public/Config/WindowConfig.hpp
)

target_link_libraries(${PROJECT_NAME} SDL3::SDL3-static flecs_static)

target_include_directories(${PROJECT_NAME} PUBLIC ${spdlog_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC Public PRIVATE Private)