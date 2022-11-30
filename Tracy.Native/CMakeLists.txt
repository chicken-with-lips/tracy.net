cmake_minimum_required(VERSION 3.14...3.23)

project(Tracy.Native VERSION 1.0 LANGUAGES CXX)

option(TRACY_ENABLE "" ON)
#option(TRACY_ON_DEMAND "" ON)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -march=native")

if (CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif ()

FetchContent_Declare (
    tracy
    GIT_REPOSITORY https://github.com/wolfpld/tracy.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(tracy)

add_library(${PROJECT_NAME} SHARED
    src/TracyClient.cpp
    ${tracy_SOURCE_DIR}/public/TracyClient.cpp
)

include_directories(
    ${tracy_SOURCE_DIR}/public/tracy
)

target_link_libraries(${PROJECT_NAME} PUBLIC TracyClient)
