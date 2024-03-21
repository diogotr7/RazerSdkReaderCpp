cmake_minimum_required(VERSION 3.28)
project(console)

set(CMAKE_CXX_STANDARD 20)

add_executable(console 
        main.cpp)

target_link_libraries(console PRIVATE RazerSdkReaderCpp)

target_include_directories(RazerSdkReaderCpp PRIVATE ${PROJECT_SOURCE_DIR}/lib)