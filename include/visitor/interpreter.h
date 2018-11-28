#pragma once

#include "ast_node.h"
#include "ivisitor.h"
#include "checked_program.h"

class Interpreter : public IVisitor
{

public:
    Interpreter() = default;
    ~Interpreter() = default;

    /**
     * Evaluate the type checked program.
     * Throws an exception in the case of a runtime error;
     *
     * @param checked_program    the type checked program
     * @return                   the result of the main method (evaluation)
     */
    double Evaluate(CheckedProgram checked_program);

private:

    static const long kMaxCallDepth = 100;

    union Value {
        double double_val;
        bool bool_val;
    }; // union Value

    SymbolTable<std::shared_ptr<Value>> typechecker_table_;
    SymbolTable<double> evaluation_table_;

    void Visit(Program* n) override;

    /*********** Functions ***********/
    void Visit(FunctionDecl* n) override;
    void Visit(FunctionParam* n) override;
    void Visit(FunctionType* n) override;

    /*********** Statements ***********/
    void Visit(Assignment* n) override;
    void Visit(Block* n) override;
    void Visit(IfThenElse* n) override;
    void Visit(While* n) override;
    void Visit(VarDecl* n) override;
    void Visit(ReturnStm* n) override;

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