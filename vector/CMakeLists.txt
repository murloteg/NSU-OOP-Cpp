cmake_minimum_required(VERSION 3.23)
project(vector)

set(CMAKE_CXX_STANDARD 17)

# add_executable(vector main.cpp)
#add_subdirectory(module_vector)
#
#target_include_directories(vector PUBLIC module_vector)
#target_link_libraries(vector PRIVATE vector_lib)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(vector vector_test.cpp)
add_subdirectory(module_vector)


target_include_directories(vector PUBLIC module_vector)
target_link_libraries(vector gtest_main)
target_link_libraries(vector vector_lib)
