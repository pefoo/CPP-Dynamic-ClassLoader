cmake_minimum_required(VERSION 3.5)

project(DynamicClassLoader LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Output dirs
#
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/runtime)
set(CMAKE_ARCHIVE_DIR ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(
  ./include
  ./test)

#
# Sub projects
#
add_subdirectory(./test/samplelib)
add_subdirectory(./include/dynamicclassloader)
add_subdirectory(./test/dynamicclassloader_test)
