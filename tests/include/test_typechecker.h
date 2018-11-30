#pragma once

#include <memory>
#include <string>
#include "test_parser.h"
#include "parser.h"
#include "program.h"
#include "checked_program.h"
#include "visitor/typechecker.h"

class TestTypeChecker : public TestParser
{
protected:

  void Check(const std::string& file) {
    std::shared_ptr<Program> program = ParseFile(file);
    TypeChecker checker;
    CheckedProgram checked_program = checker.TypeCheck(program);

    std::vector<std::string> errors = checker.GetErrors();
    if (!errors.empty()) {
        for (const std::string& s : errors) {
            std::cerr << s << std::endl;
        }
    }
    // Sanity Check
    EXPECT_TRUE(errors.empty());
  }


  std::vector<std::string> GetErrors(const std::string& file) {
    std::shared_ptr<Program> program = ParseFile(file);
    TypeChecker checker;
    CheckedProgram checked_program = checker.TypeCheck(program);

    return checker.GetErrors();
  }

}; // class TestTypeChecker