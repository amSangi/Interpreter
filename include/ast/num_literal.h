#pragma once

#include <string>
#include "expression.h"

class NumLiteral : public Expression
{
public:
	explicit NumLiteral(double value) : value_(value) {}
	virtual ~NumLiteral() = default;

	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this); }
	virtual std::string ToString()							{ 	return std::to_string(value_); }

	double GetValue() const									{	return value_; }
private:
	double value_;

}; // class NumLiteral

