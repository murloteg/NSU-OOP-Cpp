add_library(tests_lib STATIC my_tests.cpp)

target_link_libraries(tests_lib PUBLIC gtest_main game_controller_lib)
target_include_directories(tests_lib PUBLIC ../GameController)