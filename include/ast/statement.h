#pragma once

#include "ast_node.h"

class Statement : public ASTNode {
public:
    virtual bool IsReturn() const = 0;
}; // interface Statement

