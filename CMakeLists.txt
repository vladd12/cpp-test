cmake_minimum_required(VERSION 3.25)
project(cpp-test LANGUAGES CXX)

set(COMMON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")
