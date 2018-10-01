#include <memory>
#include "gtest/gtest.h"
#include "test_parser.h"


TEST_F(TestParser, SimpleProgram) {
    TestFile("SimpleProgram.txt");
}