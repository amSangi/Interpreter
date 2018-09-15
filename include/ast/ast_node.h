#pragma once

#include <memory>
#include "ivisitor.h"

class ASTNode
{
public:
	virtual ~ASTNode() = 0;
	virtual void Accept(std::shared_ptr<IVisitor> v) = 0;
}; // interface ASTNode
