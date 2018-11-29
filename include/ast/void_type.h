#pragma once

#include "static_type.h"

class VoidType : public StaticType 
{
public:
	VoidType() = default; 
	~VoidType() override = default;

	VisitorValue Accept(IVisitor* v) override               {   return v->Visit(this); }
	std::string ToString() override                         {   return "void"; }

	Type GetValue() const override                          {   return type_; }
private:
	Type type_ = VOID; 

}; // class VoidType

