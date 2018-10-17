#pragma once

#include <vector>
#include "expression.h"

class FunctionCall : public Expression
{
	typedef std::string string;
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	FunctionCall() = default;
	~FunctionCall() override = default;

	void Accept(std::shared_ptr<IVisitor> v) override   {   v->Visit(this); }
	std::string ToString() override {
		string res = identifier_name_ + "(";
		for (int i = 0; i < arguments_.size(); ++i) {
			res += arguments_[i]->ToString();
			if (i + 1 < arguments_.size()) res += ", ";
		}
		res += ")";
		return res;
	}

	void SetName(const string name)                     {   identifier_name_ = name; }
	void AddArgument(ExpPtr arg)                        {   arguments_.emplace_back(std::move(arg)); }

	string GetIdentifierName() const                    {   return identifier_name_; }
	const std::vector<ExpPtr>& GetArguments() const     {   return arguments_; }
private:
	string identifier_name_; 
	std::vector<ExpPtr> arguments_;

}; // class FunctionCall

