#pragma once

#include "statement.h"
#include "expression.h"
#include "block.h"

class While : public Statement
{
	typedef std::shared_ptr<Expression> ExpPtr;
	typedef std::shared_ptr<Block> BlockPtr;
public:
	While() = default; 
	~While() override = default;

	VisitorValue Accept(IVisitor* v) override                   {   return v->Visit(this); }
	std::string ToString() override {
		std::string res = "while (" + test_->ToString() + ")\n";
		res += block_->ToString();
		return res;
	}

	void SetPredicate(ExpPtr exp)                               {   test_  = std::move(exp); }
	void SetBlock(BlockPtr block)                               {   block_ = std::move(block); }
	ExpPtr GetPredicate() const                                 {   return test_; }
	BlockPtr GetBlock() const                                   {   return block_; }
private:
	ExpPtr test_; 
	BlockPtr block_; 

}; // class While

