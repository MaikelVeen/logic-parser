cmake_minimum_required(VERSION 3.20)
project(logic_parser C)

set(CMAKE_C_STANDARD 99)

add_executable(logic_parser main.c lexer.c reader.c token.h parser.c parser.h)
