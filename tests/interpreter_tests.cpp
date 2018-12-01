#include "test_interpreter.h"


TEST_F(TestInterpreter, Add) {
  EXPECT_EQ(1 + 2 + 3 + 4 + 100, Interpret("add.txt"));
}

TEST_F(TestInterpreter, Subtract) {
  EXPECT_EQ((-100 - (3 - (-4 - (3 - -5)))), Interpret("subtract.txt"));
}

TEST_F(TestInterpreter, Multiply) {
  EXPECT_EQ(3 * 1 * 5 * -10 * -3, Interpret("multiply.txt"));
}

TEST_F(TestInterpreter, Division) {
  EXPECT_EQ(-1000 * -35 / 10, Interpret("division.txt"));
}

TEST_F(TestInterpreter, SimpleProgram) {
  EXPECT_EQ(200, Interpret("simple_program.txt"));
}

TEST_F(TestInterpreter, ComplexProgram) {
  EXPECT_EQ(9, Interpret("complex_program.txt"));
}

TEST_F(TestInterpreter, While) {
  EXPECT_EQ(15, Interpret("while.txt"));
}

TEST_F(TestInterpreter, ParserError) {
  EXPECT_EQ(-3, Interpret("tokens.txt"));
}

TEST_F(TestInterpreter, TypeError) {
  EXPECT_EQ(-2, Interpret("return_type_mismatch.txt"));
}

TEST_F(TestInterpreter, DivideByZero) {
  EXPECT_EQ(-1, Interpret("divide_by_zero.txt"));
}