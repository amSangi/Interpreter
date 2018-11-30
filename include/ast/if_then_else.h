#pragma once

#include "expression.h"
#include "statement.h"

class IfThenElse : public Statement
{
	typedef std::shared_ptr<Expression> ExpPtr;
	typedef std::shared_ptr<Statement> StmPtr;
public:
	IfThenElse() = default; 
	~IfThenElse() override = default;

	VisitorValue Accept(IVisitor* v) override               {   return v->Visit(this); }
	bool IsReturn() const override                          {   return false; }
	std::string ToString() override {
		std::string res = "if (" + predicate_->ToString() + ")\n";
		res += then_->ToString() + "\n";
		if (else_ != nullptr) {
			res += "else\n";
			res += else_->ToString();
		}
		return res;
	}



	void SetPredicate(ExpPtr exp)                           {   predicate_ = std::move(exp); }
	void SetThen(StmPtr stm)                                {   then_ = std::move(stm); }
	void SetElse(StmPtr stm)                                {   else_ = std::move(stm); }

	ExpPtr GetPredicate() const                             {   return predicate_; }
	StmPtr GetThenStatement() const                         {   return then_; }
	StmPtr GetElseStatement() const                         {   return else_; }
private:
	ExpPtr predicate_;
	StmPtr then_;
	StmPtr else_;

}; // class IfThenElse

