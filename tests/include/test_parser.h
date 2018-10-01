#pragma once

#include <memory>
#include "test_base.h"
#include "parser.h"
#include "program.h"

class TestParser : public TestBase
{
protected:
	
    void TestFile(const std::string& filename) {
        Lexer lexer(GetFilePath(filename));
        Parser parser(lexer);
        std::shared_ptr<Program> program = parser.Parse();
        EXPECT_NE(program, nullptr);
    }

}; // class TestParser