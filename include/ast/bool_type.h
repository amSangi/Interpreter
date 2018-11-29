#pragma once

#include "static_type.h"

class BoolType : public StaticType
{
public:
	BoolType() = default;
	~BoolType() override = default;

	VisitorValue Accept(IVisitor* v) override           {   return v->Visit(this); }
	std::string ToString() override                     {   return "bool"; }

	Type GetValue() const override                      {   return type_; }
private:
	Type type_ = BOOL; 

}; // class Bool

