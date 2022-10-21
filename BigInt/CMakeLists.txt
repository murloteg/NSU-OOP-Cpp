cmake_minimum_required(VERSION 3.23)
project(BigInt)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigInt main.cpp)

add_subdirectory(BigInt_dir)

target_include_directories(BigInt PUBLIC BigInt_dir)
target_link_libraries(BigInt PRIVATE BigInt_lib)
