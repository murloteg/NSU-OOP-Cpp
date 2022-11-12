add_library(modes_lib STATIC GameMode.h GameMode.cpp Detailed/Detailed.cpp Fast/Fast.cpp Tournament/Tournament.cpp)
target_link_libraries(modes_lib PUBLIC strategies_lib game_controller_lib)
target_include_directories(modes_lib PUBLIC ../Strategies ../GameController)