cmake_minimum_required(VERSION 3.28)
project(solution)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib" "${PROJECT_SOURCE_DIR}/lib/lib_output")
add_subdirectory("${PROJECT_SOURCE_DIR}/console" "${PROJECT_SOURCE_DIR}/console/console_output")