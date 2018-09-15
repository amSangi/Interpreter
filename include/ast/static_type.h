#pragma once

#include "ast_node.h"

enum Type {
	NUMBER,
	BOOL,
	VOID,
	FUNCTION
}; // enum Type

class StaticType : public ASTNode
{
public:
	virtual ~StaticType() = 0; 
	virtual void Accept(std::shared_ptr<IVisitor> v) = 0;
	virtual Type GetType() const = 0; 

}; // class StaticType