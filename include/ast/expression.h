#pragma once

#include "ast_node.h"
#include "static_type.h"

class Expression : public ASTNode
{
	typedef std::shared_ptr<StaticType> TypePtr;
public:
	void SetType(TypePtr type)                              {   type_ = std::move(type); }
	TypePtr GetType() const                                 {   return type_; }
private:
	TypePtr type_;

}; // abstract class Expression

