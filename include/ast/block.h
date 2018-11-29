#pragma once

#include <vector>
#include "statement.h"


class Block : public Statement 
{
	typedef std::shared_ptr<Statement> StmPtr;
public:
	Block() = default;
	~Block() override = default;

	VisitorValue Accept(IVisitor* v) override                       {   return v->Visit(this); }
	std::string ToString() override {
		std::string res = "{\n";
		for (const auto &statement : statements_) {
			res += "";
			res += statement->ToString();
			res += "\n";
		}
		res += "}";
		return res;
	}

	void AddStatement(StmPtr stm)                                   {   statements_.emplace_back(std::move(stm)); }
	const std::vector<StmPtr>& GetStatements()                      {   return statements_; }

private:
	std::vector<StmPtr> statements_;

}; // class Block

