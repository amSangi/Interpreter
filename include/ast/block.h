#pragma once

#include <vector>
#include "statement.h"


class Block : public Statement 
{
	typedef std::shared_ptr<Statement> StmPtr;
public:
	Block() = default; 
	virtual ~Block() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)				{	v->Visit(this); }

	void AddStatement(StmPtr stm)									{	statements_.emplace_back(std::move(stm)); }
	const std::vector<StmPtr>& GetStatements()						{	return statements_; }

private:
	std::vector<StmPtr> statements_;

}; // class Block

