cmake_minimum_required(VERSION 3.13)
project(core C)

set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES main.c common/string_list.h common/string_list.c tokenizer/tokenizer.h tokenizer/tokenizer.c)

set(NAPI_BRIDGE_SOURCES n-api/napi-bridge.c)

if(UNIX)
    include_directories(/usr/include/node)
endif(UNIX)

if (WIN32)
    #include win32 node dir
endif (WIN32)

add_executable(${PROJECT_NAME} main.c common/string_list.h common/string_list.c tokenizer/tokenizer.h tokenizer/tokenizer.c common/token.h common/token.c)

target_link_libraries(${PROJECT_NAME} /usr/include/node)