#pragma once

#include "static_type.h"

class NumType : public StaticType
{
public:
	NumType() = default; 
	virtual ~NumType() = default; 
	
	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this);	}
	virtual std::string ToString()							{ 	return "num"; }
	
	virtual Type GetType() const							{	return type_; }
private:
	Type type_ = NUMBER; 

}; // class NumType

