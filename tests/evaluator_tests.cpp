#include <numeric>
#include "test_evaluator.h"


TEST_F(TestEvaluator, Add) {
	double result = Evaluate("add.txt");
	double expected = 1 + 2 + 3 + 4 + 100;
	EXPECT_EQ(expected, result);
}

TEST_F(TestEvaluator, Subtract) {
	double result = Evaluate("subtract.txt");
	double expected = (-100 - (3 - (-4 - (3 - -5))));
	EXPECT_EQ(expected, result);
}

TEST_F(TestEvaluator, Multiply) {
	double result = Evaluate("multiply.txt");
	double expected = 3 * 1 * 5 * -10 * -3;
	EXPECT_EQ(expected, result);
}

TEST_F(TestEvaluator, Division) {
	double result = Evaluate("division.txt");
	double expected = -1000 * -35 / 10;
	EXPECT_EQ(expected, result);
}

TEST_F(TestEvaluator, SimpleProgram) {
	double result = Evaluate("simple_program.txt");
	double expected = 200;
	EXPECT_EQ(expected, result);
}


TEST_F(TestEvaluator, ComplexProgram) {
  double result = Evaluate("complex_program.txt");
  double expected = 9;
  EXPECT_EQ(expected, result);
}


TEST_F(TestEvaluator, While) {
  double result = Evaluate("while.txt");
  double expected = 15;
  EXPECT_EQ(expected, result);
}



