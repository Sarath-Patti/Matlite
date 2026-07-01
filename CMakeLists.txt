cmake_minimum_required(VERSION 3.20)

project(
    Matlite
    VERSION 0.4.0
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

add_library(matlite_ast
    src/ast/Expression.cpp
)

target_compile_features(matlite_ast PUBLIC cxx_std_20)

target_include_directories(matlite_ast
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(matlite_ast
    PUBLIC
        matlite_lexer
)

set_target_properties(matlite_ast PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite_ast)

add_library(matlite_parser
    src/parser/Parser.cpp
)

target_compile_features(matlite_parser PUBLIC cxx_std_20)

target_include_directories(matlite_parser
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(matlite_parser
    PUBLIC
        matlite_ast
        matlite_lexer
)

set_target_properties(matlite_parser PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite_parser)

add_library(matlite_evaluator
    src/evaluator/Evaluator.cpp
)

target_compile_features(matlite_evaluator PUBLIC cxx_std_20)

target_include_directories(matlite_evaluator
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(matlite_evaluator
    PUBLIC
        matlite_ast
        matlite_lexer
)

set_target_properties(matlite_evaluator PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite_evaluator)

add_executable(matlite
    src/main.cpp
)

target_compile_features(matlite PRIVATE cxx_std_20)

target_include_directories(matlite
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(matlite
    PRIVATE
        matlite_evaluator
        matlite_parser
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

add_executable(matlite_parser_tests
    tests/parser_tests.cpp
)

target_link_libraries(matlite_parser_tests
    PRIVATE
        matlite_parser
)

target_compile_features(matlite_parser_tests PRIVATE cxx_std_20)

set_target_properties(matlite_parser_tests PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite_parser_tests)

add_test(NAME parser_tests COMMAND matlite_parser_tests)

add_executable(matlite_evaluator_tests
    tests/evaluator_tests.cpp
)

target_link_libraries(matlite_evaluator_tests
    PRIVATE
        matlite_evaluator
        matlite_parser
)

target_compile_features(matlite_evaluator_tests PRIVATE cxx_std_20)

set_target_properties(matlite_evaluator_tests PROPERTIES
    CXX_EXTENSIONS OFF
)

matlite_enable_warnings(matlite_evaluator_tests)

add_test(NAME evaluator_tests COMMAND matlite_evaluator_tests)
