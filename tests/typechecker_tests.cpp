#include <iostream>
#include "gtest/gtest.h"
#include "test_typechecker.h"


using std::vector;
using std::shared_ptr;
using std::string;


TEST_F(TestTypeChecker, Add) {
    CheckedProgram checkedProgram = Check("add.txt");
}


TEST_F(TestTypeChecker, Sub) {
    CheckedProgram checkedProgram = Check("subtract.txt");
}


TEST_F(TestTypeChecker, Multiply) {
    CheckedProgram checkedProgram = Check("multiply.txt");
}


TEST_F(TestTypeChecker, Division) {
    CheckedProgram checkedProgram = Check("division.txt");
}


TEST_F(TestTypeChecker, SimpleProgram) {
    CheckedProgram checkedProgram = Check("simple_program.txt");
}


TEST_F(TestTypeChecker, ComplexProgram) {
    CheckedProgram checkedProgram = Check("complex_program.txt");
}