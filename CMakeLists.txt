cmake_minimum_required(VERSION 3.5...3.28)

project(rekt)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Default build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")
    if(MSVC)
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /DEBUG:NONE")
    else()
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g0")
    endif()
endif()

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/Compilation"
    "${PROJECT_SOURCE_DIR}/include/Core"
    "${PROJECT_SOURCE_DIR}/include/Formatting/fmt"
    "${PROJECT_SOURCE_DIR}/include/Modules"
    "${PROJECT_SOURCE_DIR}/include/Tokenization"
    "${PROJECT_SOURCE_DIR}/include/Utilities"
)

if( BUILD_SHARED_LIBRARY ) 
    message("-- Configuring as shared library")
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
    message("-- Configuring as executable")
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()