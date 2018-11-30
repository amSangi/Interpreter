cmake_minimum_required(VERSION 3.10)
project(SimpleInterpreter)

set(CMAKE_CXX_STANDARD 17)

set(INTERPRETER_LIB_OUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(INTERPRETER_TEST_OUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)
include_directories(include/ast)
include_directories(include/lexer)
include_directories(include/visitor)

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(tests)

