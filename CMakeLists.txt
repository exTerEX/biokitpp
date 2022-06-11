cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

include(cmake/cmake-tools/Tools.cmake)

version_from_git()

project(
  biokit
  VERSION ${VERSION}
  LANGUAGES CXX
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(CMAKE_CXX_CLANG_TIDY clang-tidy --fix)
endif()
