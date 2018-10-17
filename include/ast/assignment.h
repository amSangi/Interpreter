#pragma once

#include "statement.h"
#include "expression.h"

class Assignment : public Statement
{
	typedef std::string string;
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	Assignment() = default;
	~Assignment() override = default;

	void Accept(std::shared_ptr<IVisitor> v) override   {   v->Visit(this); }
	std::string ToString() override                     {   return identifier_name_ + " = "
                                                                   + value_->ToString() + ";";}

	void SetLValue(const string value)                  {   identifier_name_ = value; }
	void SetRValue(ExpPtr value)                        {   value_ = std::move(value); }
	string GetLValue() const                            {   return identifier_name_; }
	Expression* GetRValue() const                       {   return value_.get(); }
private:
	string identifier_name_;
	ExpPtr value_;

}; // class Assignment

