#pragma once

#include <memory>
#include <string>
#include <vector>
#include "visitor/ivisitor.h"
#include "checked_program.h"
#include "static_type.h"
#include "expression.h"


class TypeChecker : public IVisitor
{
    typedef std::shared_ptr<Expression> ExpPtr;
public:
    TypeChecker() = default;
    ~TypeChecker() = default;

    /**
     * @brief          Typecheck the given program
     * @param program  The program to typecheck
     * @return         An instance of CheckedProgram
     */
    CheckedProgram TypeCheck(std::shared_ptr<Program> program);

    const std::vector<std::string>& GetErrors() const;

private:
    SymbolTable<std::shared_ptr<StaticType>> symbolTable_;
    std::string current_function_name_;
    std::vector<std::string> errors_;

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
    void Check(ExpPtr e, Type t);


    /**
     * @brief       Handle duplicate name declarations in the same scope
     * @param name  The name to check
     */
    void HandleDuplicateNameDecl(const std::string name);


    /**
     * @brief       Handle undefined identifier use
     * @param name  The undefined identifier name
     */
    void HandleUndefinedIdentifier(const std::string name);


    /**
     * @brief                  Check to see if the arguments match the parameter types
     * @param arguments        The argument expressions
     * @param parameter_types  A function's parameter types in their declared order
     */
    void CheckParameterArgumentMatch(std::vector<ExpPtr> arguments, std::vector<Type> parameter_types);


    /**
     * @brief          Log an error in 'errors_'
     * @param message  The error message
     */
    void RecordError(const std::string message);

}; // class TypeChecker