#pragma once

#include "expression.h"

class BooleanLiteral : public Expression
{
public:
	explicit BooleanLiteral(bool value) : value_(value) {}
	virtual ~BooleanLiteral() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this);	}

	bool GetValue() const									{	return value_; }
private:
	bool value_; 

}; // class BooleanLiteral

