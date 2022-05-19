cmake_minimum_required(VERSION 3.15)

project(socketcan)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)

include(cmake/Cache.cmake)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/Doxygen.cmake)
enable_doxygen()

include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

add_library(SocketCan SHARED
  src/socketcan.cpp
)

target_compile_options(SocketCan PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

target_include_directories(SocketCan
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
  PRIVATE
)

target_link_libraries(SocketCan
  PUBLIC
  PRIVATE
    glog
)

add_library(transport::SocketCan ALIAS SocketCan)

if (${BUILD_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif()
