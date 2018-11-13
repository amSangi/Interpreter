#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "token.h"
#include "input_source.h"

/**
*	A hand written lexical analyzer for a simple program. 
*	Outputs a token for each call to GetNext()
*/ 
class Lexer
{
public:

	explicit Lexer(const std::string& file_name) : input_(file_name) {}
	~Lexer() = default;

	/**
	 * @return   The next token
	 */
	Token GetNext();

	/**
	 * @return   True if there is a valid next token
	 */
	bool HasNext();

	/**
	 * @return   The current line number in the file
	 */
	size_t GetCurrentLine() const;

	/**
	 * @return   The current column number in the file
	 */
	size_t GetCurrentColumn() const; 

private:
	static const std::vector<std::string> kReservedWords;

	InputSource input_;

	Token RecognizeSymbol(char start);
	Token RecognizeIdentifier(char start);
	Token RecognizeNumber(char start);
	Token RecognizeReserved(const std::string& word);

	bool IsEndOfStatement();

}; // class Lexer


