#pragma once

#include <string> 
#include <vector>
#include "expression.h"

class FunctionCall : public Expression
{
	typedef std::string string;
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	FunctionCall() = default;
	virtual ~FunctionCall() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)	{	v->Visit(this); }

	void SetName(const string name)						{	identifier_name_ = name; }
	void AddArgument(ExpPtr arg)						{	arguments_.emplace_back(std::move(arg)); }

	string GetIdentifierName() const					{	return identifier_name_; }
	const std::vector<ExpPtr>& GetArguments() const		{	return arguments_; }
private:
	string identifier_name_; 
	std::vector<ExpPtr> arguments_;

}; // class FunctionCall

