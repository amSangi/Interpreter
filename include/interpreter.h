#pragma once

#include <string>
#include "lexer.h"
#include "parser.h"
#include "typechecker.h"
#include "evaluator.h"

class Interpreter {
public:
  static double Interpet(const std::string& filename);

}; // class Interpreter