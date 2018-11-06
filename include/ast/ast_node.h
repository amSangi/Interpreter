#pragma once

#include <memory>
#include <string>
#include "visitor/ivisitor.h"

class ASTNode
{
public:
	virtual ~ASTNode() = default;
	virtual void Accept(std::shared_ptr<IVisitor> v) = 0;
	virtual std::string ToString() = 0;

}; // interface ASTNode
