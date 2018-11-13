#pragma once

#include <memory>
#include <string>
#include "visitor/ivisitor.h"
#include "checked_program.h"
#include "static_type.h"
#include "expression.h"


class TypeChecker : public IVisitor
{
public:
    TypeChecker() = default;
    ~TypeChecker() = default;

    /**
     * @brief          Typecheck the given program
     * @param program  The program to typecheck
     * @return         An instance of CheckedProgram
     */
    CheckedProgram TypeCheck(std::shared_ptr<Program> program);

private:
    SymbolTable<StaticType*> symbolTable_;
    std::string current_function_name_;

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


    /*********** Helpers ***********/

    /**
     * @brief    Add the function to the global function symbol table
     * @param n  The function to add
     */
    void AddToFunctionTable(std::shared_ptr<FunctionDecl> n);
    /**
     * @brief       Check if the expression has a given type
     * @param e     The expression to check
     * @param type  The type to match to
     */
    void Check(Expression* e, Type t);


    /**
     * @brief       Handle duplicate name declarations in the same scope
     * @param name  The name to check
     */
    void HandleDuplicateNameDecl(const std::string name);

}; // class TypeChecker