cmake_minimum_required(VERSION 3.9)

if(${CMAKE_VERSION} VERSION_LESS 3.23)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.23)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/cmake-tools/Tools.cmake)

version_from_git()

project(
  biokit
  VERSION ${VERSION}
  LANGUAGES CXX
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

enable_testing()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  include(CTest)

  if(BUILD_TESTING)
    add_subdirectory(test)
  endif()
endif()
