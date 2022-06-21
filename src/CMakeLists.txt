include(CheckIPOSupported)

check_ipo_supported(RESULT CMP0069)

# Find all files
file(
  GLOB_RECURSE SOURCES
  LIST_DIRECTORIES false
  RELATIVE ${CMAKE_CURRENT_LIST_DIR}
  *.cpp
)

# Build library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/util> $<INSTALL_INTERFACE:include>
)

if(${CMP0069})
  set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
               CXX_STANDARD 17
               VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
               INTERPROCEDURAL_OPTIMIZATION TRUE
  )
else()
  set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
               CXX_STANDARD 17
               VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
  )
endif()
