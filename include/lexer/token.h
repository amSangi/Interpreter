#pragma once

#include <ostream>
#include <string>
#include "types.h"

/**
*	A token represents a TokenType and its corresponding value 
*	if it is an identifier or number
*/
class Token
{
public:
	Token(const TokenType type, const std::string value);
	explicit Token(const TokenType type);

	bool operator==(const Token& token) const;
	bool operator!=(const Token& token) const;

	TokenType GetType() const;
	std::string GetValue() const;

private:
	TokenType token_type_;
	std::string token_value_;

}; // class Token

