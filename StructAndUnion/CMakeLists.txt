cmake_minimum_required(VERSION 3.0)

# Setup name of the project
project(StructAndUnion)

# bring the headers .h file into the project
include_directories(include)

# Wildcard additions for source file
file(GLOB SOURCES "src/*.c")


add_executable(StructAndUnion ${SOURCES})