#pragma once

#include "ast_node.h"

enum Type {
	NUMBER,
	BOOL,
	VOID,
}; // enum Type

class StaticType : public ASTNode
{
public:
	virtual Type GetType() const = 0; 

}; // class StaticType