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

    CheckedProgram Check(const std::string& file) {
        std::shared_ptr<Program> program = ParseFile(file);
        return TypeChecker().Check(program);
    }


}; // class TestTypeChecker