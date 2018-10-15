#pragma once

#include <string>
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
	virtual ~StaticType() = default;
	virtual void Accept(std::shared_ptr<IVisitor> v) = 0;
	virtual std::string ToString() = 0;
	virtual Type GetType() const = 0; 

}; // class StaticType