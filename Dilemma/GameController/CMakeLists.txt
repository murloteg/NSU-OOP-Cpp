add_library(game_controller_lib STATIC GameController.h GameController.cpp)
target_link_libraries(game_controller_lib PUBLIC modes_lib factory_lib)
target_include_directories(game_controller_lib PUBLIC ../Modes ../Factory)