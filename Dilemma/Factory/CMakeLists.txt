add_library(factory_lib STATIC StrategyFactory.cpp)

target_link_libraries(factory_lib PUBLIC strategies_lib game_controller_lib)
target_include_directories(factory_lib PUBLIC ../Strategies ../GameController)