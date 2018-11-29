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
        explicit Value(double v) : double_val(v) {}
        explicit Value(bool v) : bool_val(v) {}
    }; // union Value

    SymbolTable<std::shared_ptr<StaticType>> typechecker_table_;
    SymbolTable<Value> evaluation_table_;
    Value current_return_value_;

    VisitorValue Visit(Program* n) override;

    /*********** Functions ***********/
    VisitorValue Visit(FunctionDecl* n) override;
    VisitorValue Visit(FunctionParam* n) override;
    VisitorValue Visit(FunctionType* n) override;

    /*********** Statements ***********/
    VisitorValue Visit(Assignment* n) override;
    VisitorValue Visit(Block* n) override;
    VisitorValue Visit(IfThenElse* n) override;
    VisitorValue Visit(While* n) override;
    VisitorValue Visit(VarDecl* n) override;
    VisitorValue Visit(ReturnStm* n) override;

    /*********** Expressions ***********/
    VisitorValue Visit(Identifier* n) override;
    VisitorValue Visit(BinaryOp* n) override;
    VisitorValue Visit(UnaryOp* n) override;
    VisitorValue Visit(FunctionCall* n) override;
    VisitorValue Visit(Conditional* n) override;
    VisitorValue Visit(NumLiteral* n) override;
    VisitorValue Visit(BooleanLiteral* n) override;

    /*********** Types ***********/
    VisitorValue Visit(NumType* n) override;
    VisitorValue Visit(BoolType* n) override;
    VisitorValue Visit(VoidType* n) override;

}; // class Interpreter