#pragma once

#include <memory>
#include <string>
#include "test_parser.h"
#include "evaluator.h"
#include "typechecker.h"
#include "parser.h"
#include "program.h"
#include "ivisitor.h"

class TestEvaluator : public TestParser
{
protected:

	double Evaluate(const std::string& file) {
		std::shared_ptr<Program> program = ParseFile(file);
		TypeChecker checker;
		Evaluator evaluator;
		return evaluator.Evaluate(checker.TypeCheck(program));
	}

}; // class TestEvaluator