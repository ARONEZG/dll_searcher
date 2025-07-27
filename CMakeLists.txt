cmake_minimum_required(VERSION 3.29)
project(dll_searcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(libpe STATIC
    libpe/libpe/libpe.ixx
)
target_sources(libpe
  PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    libpe/libpe/libpe.ixx
)

target_include_directories(libpe PUBLIC libpe/libpe)

add_executable(dll_searcher main.cpp directory.h directory.cpp walker.h walker.cpp pebinary.h pebinary.cpp filesystem_search.h filesystem_search.cpp)
target_link_libraries(dll_searcher PRIVATE libpe)



if(MSVC)
    target_compile_options(libpe PRIVATE /std:c++latest)
    target_compile_options(dll_searcher PRIVATE /std:c++latest)
endif()