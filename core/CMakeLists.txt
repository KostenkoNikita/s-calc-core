cmake_minimum_required(VERSION 3.13)
project(core C)

set(CMAKE_C_FLAGS "-std=c99")

add_executable(core main.c token_list.h token_list.c tokenizer.h tokenizer.c)