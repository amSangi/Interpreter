#pragma once

#include "statement.h"
#include "expression.h"

class ReturnStm : public Statement {
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	ReturnStm() = default; 
	~ReturnStm() override = default;

	VisitorValue Accept(IVisitor* v) override           {   return v->Visit(this); }
	std::string ToString() override                     {   return "return " + exp_->ToString() + ";"; }

	void SetExpression(ExpPtr exp)                      {   exp_ = std::move(exp); }
	ExpPtr GetExpression() const                        {   return exp_; }
private:
	ExpPtr exp_; 

}; // class ReturnStm