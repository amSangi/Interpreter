#pragma once

#include "static_type.h"

class BoolType : public StaticType
{
public:
	BoolType() = default;
	virtual ~BoolType() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)	{	v->Visit(this); }
	virtual std::string ToString()						{   return "bool"; }

	virtual Type GetType() const						{	return type_; }
private:
	Type type_ = BOOL; 

}; // class Bool

