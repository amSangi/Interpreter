project(InterpreterTest)

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/googletest/googletest-src/googletest/include)

link_directories(${INTERPRETER_LIB_OUT_PATH})

set(EXECUTABLE_OUTPUT_PATH  ${INTERPRETER_TEST_OUT_PATH})

add_executable(${PROJECT_NAME} all_tests.cpp
                               lexer_tests.cpp
                               parser_tests.cpp
                               typechecker_tests.cpp
                               evaluator_tests.cpp
                               interpreter_tests.cpp)

target_link_libraries(${PROJECT_NAME} InterpreterCore)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
