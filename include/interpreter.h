#pragma once

#include <string>
#include "lexer.h"
#include "parser.h"
#include "typechecker.h"
#include "evaluator.h"

class Interpreter {
public:
  /**
   * Interpret a given file and return the result of main
   *
   * @param filename   The file to interpret
   * @return           The return value from main
   */
  static double Interpet(const std::string& filename);

}; // class Interpreter