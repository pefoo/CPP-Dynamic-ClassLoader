set(SOURCES
  main.cpp
)
add_executable(DynamicClassLoaderTest ${SOURCES})
target_link_libraries(DynamicClassLoaderTest ${CMAKE_DL_LIBS})

add_definitions(-DRUNTIME_DIR="${CMAKE_BINARY_DIR}")
