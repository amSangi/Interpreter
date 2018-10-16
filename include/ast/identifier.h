#pragma once

#include "expression.h"

class Identifier : public Expression 
{
	typedef std::string string;
public:
	explicit Identifier(string name) : name_(name) {}
	virtual ~Identifier() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)			{	v->Visit(this); }
	virtual std::string ToString()								{	return name_; }

	string GetName() const										{	return name_; }
private:
	string name_; 

}; // class Identifier

