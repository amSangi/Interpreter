#pragma once

#include "expression.h"
#include "statement.h"

class IfThenElse : public Statement
{
	typedef std::shared_ptr<Expression> ExpPtr;
	typedef std::shared_ptr<Statement> StmPtr;
public:
	IfThenElse() = default; 
	virtual ~IfThenElse() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this); }

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

