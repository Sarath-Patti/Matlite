cmake_minimum_required(VERSION 3.20)

project(
    Matlite
    VERSION 0.1.0
    DESCRIPTION "A MATLAB-inspired interpreter"
    LANGUAGES CXX
)

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

if(MSVC)
    target_compile_options(matlite PRIVATE /W4 /permissive-)
else()
    target_compile_options(matlite PRIVATE -Wall -Wextra -Wpedantic)
endif()

