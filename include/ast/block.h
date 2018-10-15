#pragma once

#include <string>
#include <vector>
#include "statement.h"


class Block : public Statement 
{
	typedef std::shared_ptr<Statement> StmPtr;
public:
	Block() = default; 
	virtual ~Block() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)				{	v->Visit(this); }
	virtual std::string ToString()									{
		std::string res = "{\n";
		for (auto statement : statements_) {
			res += "";
			res += statement->ToString();
			res += "\n";
		}
		res += "}";
		return res;
	}

	void AddStatement(StmPtr stm)									{	statements_.emplace_back(std::move(stm)); }
	const std::vector<StmPtr>& GetStatements()						{	return statements_; }

private:
	std::vector<StmPtr> statements_;

}; // class Block

