#pragma once

#include "statement.h"
#include "expression.h"

class Assignment : public Statement
{
	typedef std::string string;
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	Assignment() = default; 
	virtual ~Assignment() = default;
	
	virtual void Accept(std::shared_ptr<IVisitor> v)	{	v->Visit(this); }
	virtual std::string ToString()						{ 	return identifier_name_ + " = " + value_->ToString() + ";";}

	void SetLValue(const string value)					{	identifier_name_ = value; }
	void SetRValue(ExpPtr value)						{	value_ = std::move(value); }
	string GetLValue() const							{	return identifier_name_; }
	Expression* GetRValue() const						{	return value_.get(); }
private:
	string identifier_name_;
	ExpPtr value_;

}; // class Assignment

