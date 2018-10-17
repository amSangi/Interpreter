#pragma once

#include "expression.h"

class Conditional : public Expression
{
	typedef std::shared_ptr<Expression> ExpPtr;
public:
	Conditional() = default; 
	~Conditional() override = default;

	void Accept(std::shared_ptr<IVisitor> v) override           {   v->Visit(this);	}
	std::string ToString() override                             {   return predicate_->ToString()
                                                                           + " ? " + tval_->ToString()
                                                                           + " : " + fval_->ToString(); }

	void SetPredicate(ExpPtr pred)                              {   predicate_ = std::move(pred); }
	void SetTrueValue(ExpPtr tval)                              {   tval_ = std::move(tval); }
	void SetFalseValue(ExpPtr fval)                             {   fval_ = std::move(fval); }

	Expression* GetPredicate() const                            {   return predicate_.get(); }
	Expression* GetTrueValue() const                            {   return tval_.get();	}
	Expression* GetFalseValue() const                           {   return fval_.get();	}
private:
	ExpPtr predicate_;
	ExpPtr tval_;
	ExpPtr	fval_;

}; // class Conditional

