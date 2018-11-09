#pragma once

#include "statement.h"
#include "expression.h"

class ReturnStm : public Statement {
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	ReturnStm() = default; 
	~ReturnStm() override = default;

	void Accept(IVisitor* v) override                   {   v->Visit(this); }
	std::string ToString() override                     {   return "return " + exp_->ToString() + ";"; }

	void SetExpression(ExpPtr exp)                      {   exp_ = std::move(exp); }
	Expression* GetExpression() const                   {   return exp_.get(); }
private:
	ExpPtr exp_; 

}; // class ReturnStm