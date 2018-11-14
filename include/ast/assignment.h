#pragma once

#include "statement.h"
#include "expression.h"
#include "identifier.h"

class Assignment : public Statement
{
	typedef std::shared_ptr<Identifier> IdPtr;
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	Assignment() = default;
	~Assignment() override = default;

	void Accept(IVisitor* v) override                   {   v->Visit(this); }
	std::string ToString() override                     {   return id_->ToString() + " = "
                                                                   + value_->ToString() + ";";}

	void SetLValue(IdPtr id)                            {   id_ = std::move(id); }
	void SetRValue(ExpPtr value)                        {   value_ = std::move(value); }
	IdPtr GetLValue() const                             {   return id_; }
	ExpPtr GetRValue() const                            {   return value_; }
private:
	IdPtr id_;
	ExpPtr value_;

}; // class Assignment

