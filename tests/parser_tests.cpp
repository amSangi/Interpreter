#include <iostream>
#include "gtest/gtest.h"
#include "test_parser.h"


using std::vector;
using std::shared_ptr;

TEST_F(TestParser, SimpleProgram) {
    auto program = ParseFile("simple_program.txt");
    SanityCheck(program);
    std::cout << program->ToString() << std::endl;
}