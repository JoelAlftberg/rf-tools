cmake_minimum_required(VERSION 3.20)
project(rf-tools)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
	source/**/*.cpp
	source/*.cpp
	lib/components/*.cpp
)

add_executable(rf-tools ${SOURCES})

target_include_directories(rf-tools PRIVATE
	include
	lib
)

target_compile_options(rf-tools PRIVATE -Wall -Werror -g -O0)