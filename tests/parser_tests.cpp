#include <iostream>
#include "gtest/gtest.h"
#include "test_parser.h"


using std::vector;
using std::shared_ptr;
using std::string;

TEST_F(TestParser, SimpleProgram) {
    auto program = ParseFile("simple_program.txt");
    SanityCheck(program);
    string actual = program->ToString();
    string expected = "num main() {\n"
                      "bool a;\n"
                      "bool b;\n"
                      "bool c;\n"
                      "bool predicate;\n"
                      "a = true;\n"
                      "b = true;\n"
                      "c = false;\n"
                      "predicate = !(((a) && (b)) || (c));\n"
                      "num value;\n"
                      "if ((predicate) && ((3.000000) > (5.000000)))\n{\n"
                      "value = 100.000000;\n"
                      "}\n"
                      "else\n{\n"
                      "value = 200.000000;\n"
                      "}\n"
                      "return value;\n"
                      "}\n";

    EXPECT_EQ(expected, actual);
}

TEST_F(TestParser, ComplexProgram) {
    auto program = ParseFile("complex_program.txt");
    SanityCheck(program);
    string actual = program->ToString();
    string expected = "num add(num x, num y) {\n"
                      "return x + y;\n"
                      "}\n"
                      "num div(num x, num y) {\n"
                      "return x / y;\n"
                      "}\n"
                      "num mul(num x, num y) {\n"
                      "return x * y;\n"
                      "}\n"
                      "num sub(num x, num y) {\n"
                      "return (x - y);\n"
                      "}\n"
                      "num gcd(num x, num y) {\n"
                      "if (x % y == 0) {\n"
                      "return y;\n"
                      "}\n"
                      "else {\n"
                      "return gcd(y, x % y);\n"
                      "}\n"
                      "}\n"
                      "num main() {\n"
                      "num x;\n"
                      "num y;\n"
                      "num z;\n"
                      "x = sub(add(100, 100), 5);\n"
                      "y = div(1500, mul(5, 3));\n"
                      "z = gcd(x, y);\n"
                      "while (z >= 0) {\n"
                      "z = sub(z, 1);\n"
                      "}\n"
                      "return z + 10;\n"
                      "}\n";
    EXPECT_EQ(expected, actual);
}
