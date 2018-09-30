#pragma once

#include "gtest/gtest.h"
#include <vector>
#include "lexer/token.h"
#include "lexer/types.h"
#include "input_source.h"
#include "lexer/lexer.h"
class TestLexer : public ::testing::Test
{
protected:

	virtual void SetUp() {}

	std::vector<Token> GetTokens(Lexer& lexer) const {
		std::vector<Token> tokens;
		Token token = lexer.GetNext();

		size_t i = 0; 
		while (token.GetType() != EndOfFileToken) {
			tokens.emplace_back(token);
			token = lexer.GetNext();
		}

		return tokens;
	}

	std::string GetFilePath(std::string filename) const {
	    // Path into examples from bin
	    std::string path = "../tests/examples/" + filename;
		return path;
	}

	void TestFile(const std::string filename, std::vector<TokenType> expected_types) const {
		Lexer lexer(GetFilePath(filename));

		std::vector<Token> tokens = GetTokens(lexer);

		ASSERT_EQ(expected_types.size(), tokens.size());
		for (size_t i = 0; i < expected_types.size(); ++i) {
			EXPECT_EQ(expected_types[i], tokens[i].GetType());
		}
	}
};