cmake_minimum_required(VERSION 3.23)
project(Dilemma)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost COMPONENTS program_options)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)

if(NOT Boost_FOUND)
    message("Not found library Boost")
    set(BOOST_REQD_SUBMODULES
            "tools/cmake;"
            "libs/program_options;"
            "libs/assert;libs/exception;libs/throw_exception;libs/static_assert;"
            "libs/bind;libs/function_types;libs/function;"
            "libs/chrono;libs/date_time;"
            "libs/concept_check;"
            "libs/config;libs/container;libs/container_hash;"
            "libs/iterator;libs/utility;libs/type_traits;libs/algorithm;;libs/conversion;libs/numeric/conversion;"
            "libs/regex;libs/unordered;libs/tokenizer;libs/move;libs/ratio;libs/lexical_cast;"
            "libs/tuple;libs/variant2;libs/typeof;libs/detail;libs/array;libs/type_index;libs/range;libs/optional;"
            "libs/smart_ptr;libs/integer;libs/rational;"
            "libs/intrusive;libs/io;"
            "libs/core;libs/align;libs/predef;libs/preprocessor;libs/system;libs/winapi;libs/atomic;"
            "libs/mpl;libs/fusion;libs/mp11;"
            "libs/any;libs/functional;"
            "libs/thread")
    include(FetchContent)
    FetchContent_Declare(
            Boost
            GIT_SUBMODULES ${BOOST_REQD_SUBMODULES}
            GIT_PROGRESS TRUE
            GIT_REPOSITORY https://github.com/boostorg/boost.git
    )
    FetchContent_MakeAvailable(Boost)
endif()

add_executable(Dilemma main.cpp)
include_directories(${BOOST_INCLUDE_LIBRARIES})

add_subdirectory(Strategies)
add_subdirectory(Factory)
add_subdirectory(GameController)
target_include_directories(Dilemma PUBLIC Strategies Factory GameController)
target_link_libraries(Dilemma PUBLIC Boost::program_options strategies_lib factory_lib game_controller_lib)
