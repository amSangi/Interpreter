#include <iostream>
#include <memory>
#include "interpreter.h"
#include "program.h"
#include "checked_program.h"

#define PARSER_ERROR_CODE     (-3)
#define TYPE_ERROR_CODE       (-2)
#define RUNTIME_ERROR_CODE    (-1)


double Interpreter::Interpet(const std::string &filename) {

  // Parse
  Parser parser(filename);
  std::shared_ptr<Program> program = parser.Parse();
  std::vector<std::string> parser_errors = parser.GetErrors();

  // Parser errors
  if (!parser_errors.empty()) {
    for (const std::string& error : parser_errors) {
      std::cerr << error << std::endl;
    }
    return PARSER_ERROR_CODE;
  }

  // TypeCheck
  TypeChecker type_checker;
  CheckedProgram checked_program = type_checker.TypeCheck(program);

  std::vector<std::string> type_errors = type_checker.GetErrors();

  // TypeCheck errors
  if (!type_errors.empty()) {
    for (const std::string& error : type_errors) {
      std::cerr << error << std::endl;
    }
    return TYPE_ERROR_CODE;
  }

  Evaluator evaluator;
  double return_value = evaluator.Evaluate(checked_program);

  std::vector<std::string> runtime_errors = evaluator.GetErrors();

  // Runtime errors
  if (!runtime_errors.empty()) {
    for (const std::string& error : runtime_errors) {
      std::cerr << error << std::endl;
    }
    return RUNTIME_ERROR_CODE;
  }

  return return_value;
}