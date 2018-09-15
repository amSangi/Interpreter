#pragma once

#include "statement.h"
#include "expression.h"
#include "block.h"

class While : public Statement
{
	typedef std::unique_ptr<Expression> ExpPtr; 
	typedef std::unique_ptr<Block> BlockPtr;
public:
	While() = default; 
	virtual ~While() = default; 
	
	virtual void Accept(std::shared_ptr<IVisitor> v)			{	v->Visit(this);	}

	void SetPredicate(ExpPtr exp)								{	test_  = std::move(exp); }
	void SetBlock(BlockPtr block)								{	block_ = std::move(block); }
	Expression* GetPredicate() const							{	return test_.get(); }
	Block* GetBlock() const										{	return block_.get(); }
private:
	ExpPtr test_; 
	BlockPtr block_; 

}; // class While

