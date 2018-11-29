#pragma once

#include <vector>
#include "expression.h"
#include "identifier.h"

class FunctionCall : public Expression
{
	typedef std::shared_ptr<Identifier> IdPtr;
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	FunctionCall() = default;
	~FunctionCall() override = default;

	VisitorValue Accept(IVisitor* v) override            {   return v->Visit(this); }
	std::string ToString() override {
		std::string res = id_->ToString() + "(";
		for (int i = 0; i < arguments_.size(); ++i) {
			res += arguments_[i]->ToString();
			if (i + 1 < arguments_.size()) res += ", ";
		}
		res += ")";
		return res;
	}

	void SetId(IdPtr id)                                {   id_ = std::move(id); }
	void AddArgument(ExpPtr arg)                        {   arguments_.emplace_back(std::move(arg)); }

	IdPtr GetId() const                                 {   return id_; }
	const std::vector<ExpPtr>& GetArguments() const     {   return arguments_; }
private:
	IdPtr id_;
	std::vector<ExpPtr> arguments_;

}; // class FunctionCall

