#pragma once

#include "expression.h"

class Identifier : public Expression 
{
	typedef std::string string;
public:
	explicit Identifier(string name) : name_(name) {}
	~Identifier() override = default;

	void Accept(IVisitor* v) override                           {   v->Visit(this); }
	std::string ToString() override                             {   return name_; }

	string GetName() const                                      {   return name_; }
private:
	string name_; 

}; // class Identifier

