#pragma once

#include <string> 
#include "expression.h"

class Identifier : public Expression 
{
	typedef std::string string;
public:
	explicit Identifier(string name) : name_(name) {}
	virtual ~Identifier() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)			{	v->Visit(this); }

	string GetName() const										{	return name_; }
private:
	string name_; 

}; // class Identifier

