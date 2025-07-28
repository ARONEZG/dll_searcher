cmake_minimum_required(VERSION 3.15)

project(unit_tests LANGUAGES CXX)

add_executable(unit_tests
    test.cpp
)

target_link_libraries(unit_tests
    GTest::gtest_main
    libpe
)

target_include_directories(unit_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}              
        ${PROJECT_SOURCE_DIR}/libpe/libpe 
)

if(MSVC)
    target_compile_options(unit_tests PRIVATE /std:c++latest)
endif()

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)
