project(Test)

include_directories(include)

link_directories(${INTERPRETER_LIB_OUT_PATH})

set(EXECUTABLE_OUTPUT_PATH  ${INTERPRETER_TEST_OUT_PATH})
include_directories(${CMAKE_SOURCE_DIR}/googletest/googletest-src/googletest/include)
add_executable(${PROJECT_NAME} all_tests.cpp lexer_tests.cpp parser_tests.cpp typechecker_tests.cpp)
target_link_libraries(${PROJECT_NAME} InterpreterCore)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
