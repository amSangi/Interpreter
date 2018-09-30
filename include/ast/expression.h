#pragma once

#include "ast_node.h"
#include "static_type.h"

class Expression : public ASTNode
{
	typedef std::shared_ptr<StaticType> TypePtr;
public:
	virtual ~Expression() = 0; 

	virtual void Accept(std::shared_ptr<IVisitor> v) = 0;
	
	void SetType(TypePtr type)								{	type_ = std::move(type); }
	StaticType* GetType() const								{	return type_.get(); }
private:
	TypePtr type_;

}; // abstract class Expression

