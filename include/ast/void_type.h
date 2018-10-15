#pragma once

#include <string>
#include "static_type.h"

class VoidType : public StaticType 
{
public:
	VoidType() = default; 
	virtual ~VoidType() = default; 
	
	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this); }
	virtual std::string ToString()							{	return "void"; }

	virtual Type GetType() const							{	return type_; }
private:
	Type type_ = VOID; 

}; // class VoidType

