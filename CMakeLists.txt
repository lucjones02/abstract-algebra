cmake_minimum_required(VERSION 3.28)
project(abstract_algebra_implementation)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/abstract_algebra.cpp
)
add_library(abstract_algebra INTERFACE)
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
target_include_directories(abstract_algebra INTERFACE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(tests)
