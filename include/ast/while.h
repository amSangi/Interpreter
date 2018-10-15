#pragma once

#include <string>
#include "statement.h"
#include "expression.h"
#include "block.h"

class While : public Statement
{
	typedef std::shared_ptr<Expression> ExpPtr;
	typedef std::shared_ptr<Block> BlockPtr;
public:
	While() = default; 
	virtual ~While() = default; 
	
	virtual void Accept(std::shared_ptr<IVisitor> v)			{	v->Visit(this);	}
	virtual std::string ToString()								{
		std::string res = "while (" + test_->ToString() + ") {\n";
		res += block_->ToString();
		res += "\n}\n";
		return res;
	}

	void SetPredicate(ExpPtr exp)								{	test_  = std::move(exp); }
	void SetBlock(BlockPtr block)								{	block_ = std::move(block); }
	Expression* GetPredicate() const							{	return test_.get(); }
	Block* GetBlock() const										{	return block_.get(); }
private:
	ExpPtr test_; 
	BlockPtr block_; 

}; // class While

