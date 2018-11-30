#include <iostream>
#include "gtest/gtest.h"
#include "test_typechecker.h"


using std::vector;
using std::shared_ptr;
using std::string;


TEST_F(TestTypeChecker, Add) {
  Check("add.txt");
}


TEST_F(TestTypeChecker, Sub) {
  Check("subtract.txt");
}


TEST_F(TestTypeChecker, Multiply) {
  Check("multiply.txt");
}

TEST_F(TestTypeChecker, Division) {
  Check("division.txt");
}


TEST_F(TestTypeChecker, SimpleProgram) {
  Check("simple_program.txt");
}


TEST_F(TestTypeChecker, ComplexProgram) {
  Check("complex_program.txt");
}


TEST_F(TestTypeChecker, BinaryOpTypeMismatch) {
  vector<string> errors = GetErrors("binary_op_type_mismatch.txt");
  ASSERT_EQ(1, errors.size());
  EXPECT_EQ("EXPECTED: BOOL RECEIVED: NUMBER", errors[0]);
}

TEST_F(TestTypeChecker, ReturnTypeMismatch) {
  vector<string> errors = GetErrors("return_type_mismatch.txt");
  ASSERT_EQ(1, errors.size());
  EXPECT_EQ("EXPECTED: NUMBER RECEIVED: BOOL", errors[0]);
}