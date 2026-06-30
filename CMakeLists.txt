cmake_minimum_required(VERSION 3.20)

project(
    Matlite
    VERSION 0.2.0
    DESCRIPTION "A MATLAB-inspired interpreter"
    LANGUAGES CXX
)

function(matlite_enable_warnings target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

add_library(matlite_lexer
    src/lexer/Lexer.cpp
    src/lexer/Token.cpp
)

target_compile_features(matlite_lexer PUBLIC cxx_std_20)

target_include_directories(matlite_lexer
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(matlite_lexer PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite_lexer)

add_executable(matlite
    src/main.cpp
)

target_compile_features(matlite PRIVATE cxx_std_20)

target_include_directories(matlite
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(matlite PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite)

enable_testing()

add_executable(matlite_lexer_tests
    tests/lexer_tests.cpp
)

target_link_libraries(matlite_lexer_tests
    PRIVATE
        matlite_lexer
)

target_compile_features(matlite_lexer_tests PRIVATE cxx_std_20)

set_target_properties(matlite_lexer_tests PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite_lexer_tests)

add_test(NAME lexer_tests COMMAND matlite_lexer_tests)
