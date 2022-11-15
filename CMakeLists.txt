cmake_minimum_required(VERSION 3.21)
project(compilers_01_29)

set(CMAKE_CXX_STANDARD 17)

add_executable(compilers_01_29 error.cpp init.cpp lexer.cpp main.cpp symbol.cpp parser.tab.cpp)
