#pragma once

#include <string>
#include "ast_node.h"

class Statement : public ASTNode
{
public:
	virtual ~Statement() = default;
	virtual void Accept(std::shared_ptr<IVisitor> v) = 0;
	virtual std::string ToString() = 0;

}; // interface Statement

