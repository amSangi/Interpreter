#include "gtest/gtest.h"

#include <fstream>
#include <sstream>
#include "lexer.h"
#include "test_lexer.h"
#include "types.h"
#include "token.h"


TEST_F(TestLexer, TestAllTokens) {

	std::vector<TokenType> expected_types{
		NumericLiteral, OpenParanToken, CloseParanToken, OpenBraceToken, CloseBraceToken, 
			CommaToken, SemiColonToken, ColonToken, LessThanToken, LessThanEqualToken, 
			GreaterThanToken, GreaterThanEqualToken, EqualEqualToken, EqualToken, 
			PlusToken, MinusToken, AsteriskToken, ForwardSlashToken, DoubleAmpersandToken, 
			AmpersandToken, ExclamationToken, DoubleBarToken, BarToken, QuestionToken, 
		IdentifierToken, IfKeyword, ElseKeyword, ReturnKeyword, TrueKeyword, FalseKeyword, 
			NumberKeyword, BoolKeyword, VoidKeyword, ForKeyword, WhileKeyword
	}; 

	TestFile("Tokens.txt", expected_types); 
}


TEST_F(TestLexer, TestSimpleAdd) {
	
	std::vector<TokenType> expected_types{
		NumberKeyword, MainKeyword, OpenParanToken, CloseParanToken, OpenBraceToken, 
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken,
			IdentifierToken, PlusToken, 
			IdentifierToken, PlusToken, 
			IdentifierToken, PlusToken, 
			IdentifierToken, PlusToken, 
			NumericLiteral, SemiColonToken, 
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	}; 
	
	TestFile("Add.txt", expected_types); 
}


TEST_F(TestLexer, TestSimpleSubtract) {

	std::vector<TokenType> expected_types{
		NumberKeyword, MainKeyword, OpenParanToken, CloseParanToken, OpenBraceToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, MinusToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken,
			MinusToken, NumericLiteral, MinusToken, 
			IdentifierToken, MinusToken,
			IdentifierToken, MinusToken, 
			IdentifierToken, MinusToken, 
			IdentifierToken, SemiColonToken,
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	};

	TestFile("Subtract.txt", expected_types); 
}


TEST_F(TestLexer, TestSimpleMultiply) {
	
	std::vector<TokenType> expected_types{
		NumberKeyword, MainKeyword, OpenParanToken, CloseParanToken, OpenBraceToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, MinusToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken,
			IdentifierToken, AsteriskToken,
			IdentifierToken, AsteriskToken,
			IdentifierToken, AsteriskToken,
			IdentifierToken, AsteriskToken,
			MinusToken, NumericLiteral, SemiColonToken, 
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	};

	TestFile("Multiply.txt", expected_types);
}


TEST_F(TestLexer, TestSimpleDivision) {

	std::vector<TokenType> expected_types{
		NumberKeyword, MainKeyword, OpenParanToken, CloseParanToken, OpenBraceToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, MinusToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken,
			IdentifierToken, AsteriskToken, 
			MinusToken, IdentifierToken, ForwardSlashToken, 
			IdentifierToken, SemiColonToken, 
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	};
	
	TestFile("Division.txt", expected_types);
}


TEST_F(TestLexer, TestSimpleProgram) {

	std::vector<TokenType> expected_types{
		NumberKeyword, MainKeyword, OpenParanToken, CloseParanToken, OpenBraceToken,
		BoolKeyword, IdentifierToken, EqualToken, TrueKeyword, SemiColonToken, 
		BoolKeyword, IdentifierToken, EqualToken, FalseKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken, TrueKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken, 
			ExclamationToken, OpenParanToken, IdentifierToken, DoubleAmpersandToken, 
			IdentifierToken, CloseParanToken, DoubleBarToken, IdentifierToken, SemiColonToken, 
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, 
		IfKeyword, OpenParanToken, IdentifierToken, DoubleAmpersandToken, NumericLiteral, 
			GreaterThanToken, NumericLiteral, CloseParanToken, OpenBraceToken, 
			IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken, 
		ElseKeyword, OpenBraceToken, 
			IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken, 
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	};

	TestFile("SimpleProgram.txt", expected_types); 
}


TEST_F(TestLexer, TestCopyConstructor) {

	std::vector<TokenType> expected_types{
		NumberKeyword, MainKeyword, OpenParanToken, CloseParanToken, OpenBraceToken,
		BoolKeyword, IdentifierToken, EqualToken, TrueKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken, FalseKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken, TrueKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken,
		ExclamationToken, OpenParanToken, IdentifierToken, DoubleAmpersandToken,
		IdentifierToken, CloseParanToken, DoubleBarToken, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IfKeyword, OpenParanToken, IdentifierToken, DoubleAmpersandToken, NumericLiteral,
		GreaterThanToken, NumericLiteral, CloseParanToken, OpenBraceToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken,
		ElseKeyword, OpenBraceToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken,
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	};

	std::ifstream in_file(GetFilePath("SimpleProgram.txt"));
	ASSERT_TRUE(in_file.is_open());

	InputSource source(in_file);
	Lexer a(source);
	Lexer b(a);


	Token token = a.GetNext();
	std::vector<Token> tokens;
	for (size_t i = 0; i < expected_types.size() / 2; ++i) {
		tokens.emplace_back(token);
		token = a.GetNext();
	}

	while (token.GetType() != EndOfFileToken) {
		tokens.emplace_back(token);
		token = b.GetNext();
	}

	for (size_t i = 0; i < expected_types.size(); ++i) {
		EXPECT_EQ(expected_types[i], tokens[i].GetType());
	}

	EXPECT_EQ(a.GetCurrentColumn(), b.GetCurrentColumn());
	EXPECT_EQ(a.GetCurrentLine(), b.GetCurrentLine());
}


TEST_F(TestLexer, TestAssignmentOperator) {
	std::vector<TokenType> expected_types{
		NumberKeyword, MainKeyword, OpenParanToken, CloseParanToken, OpenBraceToken,
		BoolKeyword, IdentifierToken, EqualToken, TrueKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken, FalseKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken, TrueKeyword, SemiColonToken,
		BoolKeyword, IdentifierToken, EqualToken,
		ExclamationToken, OpenParanToken, IdentifierToken, DoubleAmpersandToken,
		IdentifierToken, CloseParanToken, DoubleBarToken, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IfKeyword, OpenParanToken, IdentifierToken, DoubleAmpersandToken, NumericLiteral,
		GreaterThanToken, NumericLiteral, CloseParanToken, OpenBraceToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken,
		ElseKeyword, OpenBraceToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken,
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	};

	std::ifstream in_file(GetFilePath("SimpleProgram.txt"));
	ASSERT_TRUE(in_file.is_open());

	InputSource source(in_file);
	Lexer a(source);
	Lexer b = a;


	Token token = a.GetNext();
	std::vector<Token> tokens;
	for (size_t i = 0; i < expected_types.size() / 2; ++i) {
		tokens.emplace_back(token);
		token = a.GetNext();
	}

	while (token.GetType() != EndOfFileToken) {
		tokens.emplace_back(token);
		token = b.GetNext();
	}

	for (size_t i = 0; i < expected_types.size(); ++i) {
		EXPECT_EQ(expected_types[i], tokens[i].GetType());
	}

	EXPECT_EQ(a.GetCurrentColumn(), b.GetCurrentColumn());
	EXPECT_EQ(a.GetCurrentLine(), b.GetCurrentLine());
}