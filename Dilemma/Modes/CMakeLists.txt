add_library(modes_lib STATIC GameMode.h Detailed.cpp)
target_link_libraries(modes_lib PUBLIC strategies_lib)
target_include_directories(modes_lib PUBLIC ../Strategies)