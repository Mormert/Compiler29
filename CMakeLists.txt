cmake_minimum_required(VERSION 3.21)
project(compilers_01_29)

set(CMAKE_CXX_STANDARD 17)

include_directories(StackMachine)

add_executable(compilers_01_29 error.cpp init.cpp lexer.cpp main.cpp symbol.cpp parser.tab.cpp TreeNode.cpp StackMachine/StackMachine.cpp)

# Compile the lexer.l and parser.ypp to C and C++ code with
# flex lexer.l
# bison parser.ypp -d