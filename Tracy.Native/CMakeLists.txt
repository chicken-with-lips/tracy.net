cmake_minimum_required(VERSION 3.14...3.23)

project(Tracy.Native VERSION 1.0 LANGUAGES CXX)

option(TRACY_ENABLE "" ON)
#option(TRACY_ON_DEMAND "" ON)

include(FetchContent)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

if(WIN32)    
    set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS /DEBUG:FASTLINK")
    set(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE "x64")

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

        if (USE_STATIC_MSVC_RUNTIME_LIBRARY)
		    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	    else()
		    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
	    endif()
    endif()
elseif(LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -I. -Wall -Werror")
endif()

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
