#pragma once

#include "statement.h"
#include "expression.h"

class ReturnStm : public Statement {
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	ReturnStm() = default; 
	virtual ~ReturnStm() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)	{ 	v->Visit(this); }
	virtual std::string ToString()						{	return "return " + exp_->ToString() + ";"; }

	void SetExpression(ExpPtr exp)						{	exp_ = std::move(exp); }
	Expression* GetExpression() const					{	return exp_.get(); }
private:
	ExpPtr exp_; 

}; // class ReturnStm