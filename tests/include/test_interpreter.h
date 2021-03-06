#pragma once

#include "test_base.h"
#include "interpreter.h"

class TestInterpreter : public TestBase
{
protected:

  double Interpret(const std::string& filename) {
    return Interpreter::Interpret(GetFilePath(filename));
  }

}; // class TestInterpreter