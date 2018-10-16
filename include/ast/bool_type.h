#pragma once

#include "static_type.h"

class BoolType : public StaticType
{
public:
	BoolType() = default;
	~BoolType() override = default;

	void Accept(std::shared_ptr<IVisitor> v) override 	{	v->Visit(this); }
	std::string ToString() override 					{   return "bool"; }

	Type GetType() const override						{	return type_; }
private:
	Type type_ = BOOL; 

}; // class Bool

