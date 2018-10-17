#pragma once

#include "static_type.h"

class NumType : public StaticType
{
public:
	NumType() = default; 
	~NumType() override = default;
	
	void Accept(std::shared_ptr<IVisitor> v) override       {   v->Visit(this);	}
	std::string ToString() override                         {   return "num"; }
	
	Type GetType() const override                           {   return type_; }
private:
	Type type_ = NUMBER; 

}; // class NumType

