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

	void Accept(std::shared_ptr<IVisitor> v) override		{	v->Visit(this); }
	std::string ToString() override 						{
		std::string res = "if (" + predicate_->ToString() + ")\n";
		res += then_->ToString() + "\n";
		if (else_ != nullptr) {
			res += "else\n";
			res += else_->ToString();
		}
		return res;
	}



	void SetPredicate(ExpPtr exp)							{	predicate_ = std::move(exp); }
	void SetThen(StmPtr stm)								{	then_ = std::move(stm); }
	void SetElse(StmPtr stm)								{	else_ = std::move(stm); }

	Expression* GetPredicate() const						{	return predicate_.get(); }
	Statement* GetThenStatement() const						{	return then_.get(); }
	Statement* GetElseStatement() const						{	return else_.get(); }
private:
	ExpPtr predicate_;
	StmPtr then_;
	StmPtr else_;

}; // class IfThenElse

