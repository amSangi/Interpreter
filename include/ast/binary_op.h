#pragma once

#include <string>
#include "expression.h"
#include "operator.h"

class BinaryOp : public Expression
{
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	BinaryOp() = default; 
	virtual ~BinaryOp() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)			{	v->Visit(this); }
	virtual std::string ToString()								{	return "(" + left_->ToString() + ")"
																		  	+ " " + BOpToString(op_) + " "
																			+ "(" + right_->ToString() + ")"; }

	void SetOperator(BOperator op)								{	op_ = op; }
	void SetLeft(ExpPtr left)									{	left_ = std::move(left); }
	void SetRight(ExpPtr right)									{	right_ = std::move(right);  }

	BOperator GetOperator() const								{	return op_; }
	Expression* GetLeft() const									{	return left_.get(); }
	Expression* GetRight() const								{	return right_.get(); }
private:
	BOperator op_; 
	ExpPtr left_;
	ExpPtr right_;

}; // class BinaryOp
