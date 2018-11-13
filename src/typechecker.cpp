#include <utility>
#include "visitor/typechecker.h"
#include "ast.h"

using std::make_shared;

CheckedProgram TypeChecker::TypeCheck(std::shared_ptr<Program> program){
    program->Accept(this);
    return CheckedProgram(std::move(program), symbolTable_);
}

void TypeChecker::Visit(Program* n) {
    // Build function table
    for (const auto& fun_decl : n->GetFunctions()) {
        AddToFunctionTable(fun_decl);
    }

    for (const auto& fun_decl : n->GetFunctions()) {
        fun_decl->Accept(this);
    }
    n->GetMain()->Accept(this);
}


/* ---------- Functions ---------- */
void TypeChecker::Visit(FunctionDecl* n) {
    current_function_name_ = n->GetId()->GetName();
    for (const auto& statement : n->GetStatements()) {
        statement->Accept(this);
    }
}

// Types already set by parser
void TypeChecker::Visit(FunctionParam* n) {}
void TypeChecker::Visit(FunctionType* n) {}

/* ---------- Statements ---------- */
void TypeChecker::Visit(Assignment* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(Block* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(IfThenElse* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(While* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(VarDecl* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(ReturnStm* n) {
    // TODO: Finish Implementation
}

/* ---------- Expressions ---------- */
void TypeChecker::Visit(Identifier* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(BinaryOp* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(UnaryOp* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(FunctionCall* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(Conditional* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(NumLiteral* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(BooleanLiteral* n) {
    // TODO: Finish Implementation
}

/* ---------- Types ---------- */
void TypeChecker::Visit(NumType* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(BoolType* n) {
    // TODO: Finish Implementation
}

void TypeChecker::Visit(VoidType* n) {
    // TODO: Finish Implementation
}


/* ---------- Helpers ---------- */

void TypeChecker::AddToFunctionTable(std::shared_ptr<FunctionDecl> n) {
    auto type = make_shared<FunctionType>();
    for (const auto& formal : n->GetFormals()) {
        type->AddParamType(formal->GetType()->GetValue());
    }
    type->SetReturnType(n->GetReturnType()->GetValue());
    symbolTable_.PutFunction(n->GetId()->GetName(), type);
}

void TypeChecker::Check(Expression* e, Type type) {
    // Error Handling
    // TODO: Finish Implementation
}