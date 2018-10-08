#include "gtest/gtest.h"

#include <fstream>
#include "lexer.h"
#include "test_lexer.h"


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
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken,
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
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,

        IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, MinusToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken,
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
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, MinusToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken,
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
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		NumberKeyword, IdentifierToken, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, MinusToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken, NumericLiteral, SemiColonToken,
		IdentifierToken, EqualToken,
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
		BoolKeyword, IdentifierToken, SemiColonToken,
		BoolKeyword, IdentifierToken, SemiColonToken,
		BoolKeyword, IdentifierToken, SemiColonToken,
		BoolKeyword, IdentifierToken, SemiColonToken,
		IdentifierToken, EqualToken, TrueKeyword, SemiColonToken,
		IdentifierToken, EqualToken, TrueKeyword, SemiColonToken,
		IdentifierToken, EqualToken, FalseKeyword, SemiColonToken,
		IdentifierToken, EqualToken,
			ExclamationToken, OpenParanToken, IdentifierToken, DoubleAmpersandToken, 
			IdentifierToken, CloseParanToken, DoubleBarToken, IdentifierToken, SemiColonToken, 
		NumberKeyword, IdentifierToken, SemiColonToken,
		IfKeyword, OpenParanToken, IdentifierToken, DoubleAmpersandToken, NumericLiteral, 
			GreaterThanToken, NumericLiteral, CloseParanToken, OpenBraceToken, 
			IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken, 
		ElseKeyword, OpenBraceToken, 
			IdentifierToken, EqualToken, NumericLiteral, SemiColonToken, CloseBraceToken, 
		ReturnKeyword, IdentifierToken, SemiColonToken, CloseBraceToken
	};

	TestFile("SimpleProgram.txt", expected_types); 
}