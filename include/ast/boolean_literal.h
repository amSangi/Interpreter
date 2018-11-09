#pragma once

#include "expression.h"

class BooleanLiteral : public Expression
{
public:
	explicit BooleanLiteral(bool value) : value_(value) {}
	~BooleanLiteral() override = default;

	void Accept(IVisitor* v) override                       {   v->Visit(this); }
	std::string ToString() override                         {   return value_ ? "true" : "false"; }

	bool GetValue() const                                   {   return value_; }
private:
	bool value_; 

}; // class BooleanLiteral

