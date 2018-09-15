#pragma once

#include "ast_node.h"

class Statement : public ASTNode
{
public:
	virtual ~Statement() = 0; 
	virtual void Accept(std::shared_ptr<IVisitor> v) = 0;

}; // interface Statement

