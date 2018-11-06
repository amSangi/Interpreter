#pragma once

#include "ast_node.h"
#include "ivisitor.h"

class Interpreter : public IVisitor
{

public:
    Interpreter() = default;
    ~Interpreter() = default;

    int Evaluate(std::shared_ptr<Program> program);

private:
    void Visit(Program* n) override;

    /*********** Statements ***********/
    void Visit(Assignment* n) override;
    void Visit(Block* n) override;
    void Visit(IfThenElse* n) override;
    void Visit(While* n) override;
    void Visit(VarDecl* n) override;
    void Visit(ReturnStm* n) override;

    /*********** Functions ***********/
    void Visit(FunctionDecl* n) override;
    void Visit(MainFunction* n) override;
    void Visit(FunctionParam* n) override;

    /*********** Expressions ***********/
    void Visit(Identifier* n) override;
    void Visit(BinaryOp* n) override;
    void Visit(UnaryOp* n) override;
    void Visit(FunctionCall* n) override;
    void Visit(Conditional* n) override;
    void Visit(NumLiteral* n) override;
    void Visit(BooleanLiteral* n) override;

    /*********** Types ***********/
    void Visit(NumType* n) override;
    void Visit(BoolType* n) override;
    void Visit(VoidType* n) override;

}; // class Interpreter