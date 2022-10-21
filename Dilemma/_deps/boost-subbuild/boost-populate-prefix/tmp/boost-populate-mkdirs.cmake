# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-src"
  "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-build"
  "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-subbuild/boost-populate-prefix"
  "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-subbuild/boost-populate-prefix/tmp"
  "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp"
  "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-subbuild/boost-populate-prefix/src"
  "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/mac/CLionProjects/Cpp-Projects/Dilemma/_deps/boost-subbuild/boost-populate-prefix/src/boost-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()