#pragma once

#include <utility>
#include "expression.h"

class Identifier : public Expression 
{
	typedef std::string string;
public:
	explicit Identifier(string name) : name_(std::move(name)) {}
	~Identifier() override = default;

	VisitorValue Accept(IVisitor* v) override                   {   return v->Visit(this); }
	std::string ToString() override                             {   return name_; }

	string GetName() const                                      {   return name_; }
private:
	string name_; 

}; // class Identifier

