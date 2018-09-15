#pragma once

#include <string> 
#include "statement.h"
#include "static_type.h"

class VarDecl : public Statement 
{
	typedef std::string string;
	typedef std::unique_ptr<StaticType> TypePtr;
public:
	VarDecl() = default; 
	virtual ~VarDecl() = default; 

	virtual void Accept(std::shared_ptr<IVisitor> v)		{	v->Visit(this); }

	void SetType(TypePtr type)								{	type_ = std::move(type); }
	void SetName(const string name)							{	identifier_name_ = name; }
	StaticType* GetType() const								{	return type_.get(); }
	string GetVarName() const								{	return identifier_name_; }
private:
	TypePtr type_; 
	string identifier_name_; 

}; // class VarDecl