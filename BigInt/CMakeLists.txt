cmake_minimum_required(VERSION 3.23)
project(BigInt)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(BigInt Tests/my_tests.cpp)
#add_executable(BigInt Tests/all_tests.cpp)
add_subdirectory(BigInt_dir)
target_include_directories(BigInt PUBLIC BigInt_dir)
target_link_libraries(BigInt PRIVATE gtest_main)
target_link_libraries(BigInt PRIVATE BigInt_lib)

