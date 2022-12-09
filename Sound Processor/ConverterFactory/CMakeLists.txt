add_library(factory_lib STATIC Factory.h Factory.cpp)
target_include_directories(factory_lib PUBLIC ../Converters)
target_link_libraries(factory_lib PUBLIC converters_lib)