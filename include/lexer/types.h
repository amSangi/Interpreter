#pragma once

enum TokenType {
	// Literals
	NumericLiteral,						// [0-9]+ (".")? [0-9]*

	// Punctuation 
	OpenParanToken,						// (
	CloseParanToken,					// )
	OpenBraceToken,						// {
	CloseBraceToken,					// }
	CommaToken,							// , 
	SemiColonToken,						// ;
	ColonToken,							// :
	LessThanToken,						// <
	LessThanEqualToken,					// <=
	GreaterThanToken,					// >
	GreaterThanEqualToken,				// >=
	EqualEqualToken,					// ==
	EqualToken,							// = 
	PlusToken,							// +
	MinusToken,							// -
	AsteriskToken,						// *
	ForwardSlashToken,					// / 
	DoubleAmpersandToken,				// &&
	AmpersandToken,						// &
	ExclamationToken,					// !
	DoubleBarToken,						// ||
	BarToken,							// |
	QuestionToken,						// ?

	// Identifier
	IdentifierToken,					// ( "_" | [a-z, A-Z] ) ("_" | [a-z, A-Z] | [0-9])*

	// Reserved
	IfKeyword,							// if
	ElseKeyword,						// else
	ReturnKeyword,						// return
	WhileKeyword,						// while
	ForKeyword,							// for
	TrueKeyword,						// true
	FalseKeyword,						// false
	NumberKeyword,						// num
	BoolKeyword,						// bool
	VoidKeyword,						// void
	MainKeyword,						// main


	// End
	EndOfFileToken,

	// Invalid
	InvalidToken

}; // enum TokenType
