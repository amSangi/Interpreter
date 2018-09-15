#pragma once

#include "expression.h"
#include "operator.h"

class UnaryOp : public Expression
{
	typedef std::unique_ptr<Expression> ExpPtr; 
public:
	UnaryOp() = default; 
	virtual ~UnaryOp() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this);	}

	void SetExpression(ExpPtr exp)							{	expression_ = std::move(exp); }
	void SetOp(UOperator op)								{	op_ = op; }
	UOperator GetOperator() const							{	return op_; }
	Expression* GetExpression() const						{	return expression_.get(); }
private:
	UOperator op_; 
	ExpPtr expression_;

}; // class UnaryOp

