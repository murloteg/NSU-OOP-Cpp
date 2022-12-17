add_library(description_lib STATIC Description.cpp Description.h)
target_include_directories(description_lib PUBLIC ../Converters)
target_link_libraries(description_lib PUBLIC converters_lib)