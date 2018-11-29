#pragma once

#include "expression.h"
#include "operator.h"

class UnaryOp : public Expression
{
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	UnaryOp() = default; 
	~UnaryOp() override = default;

	VisitorValue Accept(IVisitor* v) override               {   return v->Visit(this); }
	std::string ToString() override                         {   return UOpToString(op_)
                                                                       + "(" + exp_->ToString() + ")"; }

	void SetExpression(ExpPtr exp)                          {   exp_ = std::move(exp); }
	void SetOp(UOperator op)                                {   op_ = op; }
	UOperator GetOperator() const                           {   return op_; }
	ExpPtr GetExpression() const                            {   return exp_; }
private:
	UOperator op_; 
	ExpPtr exp_;

}; // class UnaryOp

