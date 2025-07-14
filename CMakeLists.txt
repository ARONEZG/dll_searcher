cmake_minimum_required(VERSION 3.29)
project(dll_searcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Альтернативный способ добавления модуля
add_library(libpe 
    libpe/libpe/libpe.ixx
)

# Указываем, что это модуль
set_target_properties(libpe PROPERTIES
    CXX_SCAN_FOR_MODULES ON
)

# Добавляем директорию для поиска модулей
target_include_directories(libpe PUBLIC libpe/libpe)

add_executable(dll_searcher main.cpp)
target_link_libraries(dll_searcher PRIVATE libpe)

# Для Visual Studio - дополнительные флаги
if(MSVC)
    target_compile_options(libpe PRIVATE /std:c++latest)
    target_compile_options(dll_searcher PRIVATE /std:c++latest)
endif()