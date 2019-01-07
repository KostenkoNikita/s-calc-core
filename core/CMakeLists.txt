cmake_minimum_required(VERSION 3.13)
project(core C)

set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES main.c string_list.h string_list.c tokenizer.h tokenizer.c)

set(NAPI_BRIDGE_SOURCES napi-bridge.c)

if(UNIX)
    include_directories(/usr/include/node)
endif(UNIX)

add_executable(${PROJECT_NAME} main.c string_list.h string_list.c tokenizer.h tokenizer.c)

target_link_libraries(${PROJECT_NAME} /usr/include/node)