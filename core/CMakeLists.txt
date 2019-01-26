cmake_minimum_required(VERSION 3.13)
project(core C)

set(CMAKE_C_FLAGS "-std=c99")

set(COMMON_SOURCES common/string_list.c common/string_list.h common/token.c common/token.h)

set(STATUS_SOURCES status/status.c status/status.h)

set(TOKENIZER_SOURCES tokenizer/tokenizer.c tokenizer/tokenizer.h common/token_stack.h common/token_stack.c)

set(NAPI_BRIDGE_SOURCES n-api/napi-bridge.c)

add_executable(${PROJECT_NAME} main.c ${COMMON_SOURCES} ${STATUS_SOURCES} ${TOKENIZER_SOURCES})

if(UNIX AND NOT APPLE)
    include_directories(/usr/include/node)
    target_link_libraries(${PROJECT_NAME} /usr/include/node)
endif(UNIX AND NOT APPLE)