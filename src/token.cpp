#include "token.h"


Token::Token(const TokenType type, const std::string value)
	: token_type_(type), token_value_(value) {}

Token::Token(const TokenType type)
	: token_type_(type) {}

bool Token::operator==(const Token & token) const
{
	return token.token_type_ == token_type_ && token.token_value_ == token_value_;
}

bool Token::operator!=(const Token & token) const
{
	return !(*this == token);
}

TokenType Token::GetType() const {
	return token_type_;
}

std::string Token::GetValue() const {
	return token_value_;
}

