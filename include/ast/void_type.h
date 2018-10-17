#pragma once

#include "static_type.h"

class VoidType : public StaticType 
{
public:
	VoidType() = default; 
	~VoidType() override = default;
	
	void Accept(std::shared_ptr<IVisitor> v) override       {   v->Visit(this); }
	std::string ToString() override                         {   return "void"; }

	Type GetType() const override                           {   return type_; }
private:
	Type type_ = VOID; 

}; // class VoidType

