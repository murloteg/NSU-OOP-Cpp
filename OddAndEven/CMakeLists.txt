cmake_minimum_required(VERSION 3.23)
project(OddAndEven)

SET(VERSION_CXX_STANDARD 17)

add_executable(OddAndEven main.cpp)

add_subdirectory(MyFunction_lib)
target_include_directories(OddAndEven PUBLIC MyFunction_lib)
target_link_libraries(OddAndEven PRIVATE OddAndEven_lib)
