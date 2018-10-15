#pragma once

#include <memory>
#include "test_base.h"
#include "parser.h"
#include "program.h"

class TestParser : public TestBase
{
protected:
	
    std::shared_ptr<Program> ParseFile(const std::string& filename) {
        Lexer lexer(GetFilePath(filename));
        Parser parser(lexer);
        return parser.Parse();
    }

    void SanityCheck(const std::shared_ptr<Program> program) {
        ASSERT_NE(nullptr, program);
        auto functions = program->GetFunctions();
        auto main = program->GetMain();
        ASSERT_NE(nullptr, main);
    }

}; // class TestParser