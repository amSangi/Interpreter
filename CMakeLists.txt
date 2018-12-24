cmake_minimum_required(VERSION 3.10)
project(Interpreter)

set(CMAKE_CXX_STANDARD 17)

# Set build output paths
set(INTERPRETER_LIB_OUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(INTERPRETER_EXE_OUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(INTERPRETER_TEST_OUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Include main headers
include_directories(include)
include_directories(include/ast)
include_directories(include/lexer)
include_directories(include/visitor)

# Create InterpreterCore and Tests
add_subdirectory(src)
add_subdirectory(lib/googletest)
add_subdirectory(tests)

# Build Interpreter
set(EXECUTABLE_OUTPUT_PATH ${INTERPRETER_EXE_OUT_PATH})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} InterpreterCore)