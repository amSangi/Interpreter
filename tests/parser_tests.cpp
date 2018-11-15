#include <iostream>
#include "gtest/gtest.h"
#include "test_parser.h"


using std::vector;
using std::shared_ptr;
using std::string;

TEST_F(TestParser, Add) {
    auto program = ParseFile("add.txt");
    SanityCheck(program);
    string actual = program->ToString();
    string expected = "num main() {\n"
                      "num a;\n"
                      "num b;\n"
                      "num c;\n"
                      "num d;\n"
                      "num sum;\n"
                      "a = 1.000000;\n"
                      "b = 2.000000;\n"
                      "c = 3.000000;\n"
                      "d = 4.000000;\n"
                      "sum = (a) + ((b) + ((c) + ((d) + (100.000000))));\n"
                      "return sum;\n"
                      "}\n";
    EXPECT_EQ(expected, actual);
}

TEST_F(TestParser, Sub) {
    auto program = ParseFile("subtract.txt");
    SanityCheck(program);
    string actual = program->ToString();
    string expected = "num main() {\n"
                      "num a;\n"
                      "num b;\n"
                      "num c;\n"
                      "num d;\n"
                      "num total;\n"
                      "a = 3.000000;\n"
                      "b = (-1.000000) * (4.000000);\n"
                      "c = 3.000000;\n"
                      "d = 5.000000;\n"
                      "total = ((-1.000000) * (100.000000)) - ((a) - ((b) - ((c) - ((-1.000000) * (d)))));\n"
                      "return total;\n"
                      "}\n";
    EXPECT_EQ(expected, actual);
}

TEST_F(TestParser, Multiply) {
    auto program = ParseFile("multiply.txt");
    SanityCheck(program);
    string actual = program->ToString();
    string expected = "num main() {\n"
                      "num a;\n"
                      "num b;\n"
                      "num c;\n"
                      "num d;\n"
                      "num product;\n"
                      "a = 3.000000;\n"
                      "b = 1.000000;\n"
                      "c = 5.000000;\n"
                      "d = (-1.000000) * (10.000000);\n"
                      "product = (a) * ((b) * ((c) * ((d) * ((-1.000000) * (3.000000)))));\n"
                      "return product;\n"
                      "}\n";
    EXPECT_EQ(expected, actual);
}

TEST_F(TestParser, Division) {
    auto program = ParseFile("division.txt");
    SanityCheck(program);
    string actual = program->ToString();
    string expected = "num main() {\n"
                      "num a;\n"
                      "num b;\n"
                      "num c;\n"
                      "num result;\n"
                      "a = 10.000000;\n"
                      "b = (-1.000000) * (1000.000000);\n"
                      "c = 35.000000;\n"
                      "result = (b) * (((-1.000000) * (c)) / (a));\n"
                      "return result;\n"
                      "}\n";
    EXPECT_EQ(expected, actual);
}

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
                      "return (x) + (y);\n"
                      "}\n"
                      "num div(num x, num y) {\n"
                      "return (x) / (y);\n"
                      "}\n"
                      "num mul(num x, num y) {\n"
                      "return (x) * (y);\n"
                      "}\n"
                      "num sub(num x, num y) {\n"
                      "return (x) - (y);\n"
                      "}\n"
                      "num gcd(num x, num y) {\n"
                      "if (((x) % (y)) == (0.000000))\n{\n"
                      "return y;\n"
                      "}\n"
                      "else\n{\n"
                      "return gcd(y, (x) % (y));\n"
                      "}\n"
                      "}\n"
                      "num main() {\n"
                      "num x;\n"
                      "num y;\n"
                      "num z;\n"
                      "x = sub(add(100.000000, 100.000000), 5.000000);\n"
                      "y = div(1500.000000, mul(5.000000, 3.000000));\n"
                      "z = gcd(x, y);\n"
                      "while ((z) >= (0.000000))\n{\n"
                      "z = sub(z, 1.000000);\n"
                      "}\n"
                      "return (z) + (10.000000);\n"
                      "}\n";
    EXPECT_EQ(expected, actual);
}
