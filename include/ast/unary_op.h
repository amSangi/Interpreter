#pragma once

#include <string>
#include "expression.h"
#include "operator.h"

class UnaryOp : public Expression
{
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	UnaryOp() = default; 
	virtual ~UnaryOp() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this);	}
	virtual std::string ToString()							{ 	return UOpToString(op_)
																	  	+ "(" + exp_->ToString() + ")"; }

	void SetExpression(ExpPtr exp)							{	exp_ = std::move(exp); }
	void SetOp(UOperator op)								{	op_ = op; }
	UOperator GetOperator() const							{	return op_; }
	Expression* GetExpression() const						{	return exp_.get(); }
private:
	UOperator op_; 
	ExpPtr exp_;

}; // class UnaryOp

