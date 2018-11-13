#include <utility>
#include "visitor/typechecker.h"
#include "ast.h"

using std::make_shared;
using std::string;

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
    auto l_value = n->GetLValue();
    auto r_value = n->GetRValue();
    l_value->Accept(this);
    r_value->Accept(this);
    Check(l_value, r_value->GetType()->GetValue());
}

void TypeChecker::Visit(Block* n) {
    for (const auto& statement : n->GetStatements()) {
        statement->Accept(this);
    }
}

void TypeChecker::Visit(IfThenElse* n) {
    auto predicate = n->GetPredicate();
    auto then = n->GetThenStatement();
    auto els = n->GetElseStatement();
    predicate->Accept(this);
    Check(predicate, BOOL);
    then->Accept(this);
    if (els != nullptr) els->Accept(this);
}

void TypeChecker::Visit(While* n) {
    auto predicate = n->GetPredicate();
    auto block = n->GetBlock();
    predicate->Accept(this);
    Check(predicate, BOOL);
    block->Accept(this);
}

void TypeChecker::Visit(VarDecl* n) {
    auto id = n->GetId();
    auto type = n->GetType();
    string name = id->GetName();
    if (symbolTable_.Get(name)) HandleDuplicateNameDecl(name);
    symbolTable_.Put(name, type);
}

void TypeChecker::Visit(ReturnStm* n) {
    n->GetExpression()->Accept(this);
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

// Do nothing
void TypeChecker::Visit(NumType* n) {}
void TypeChecker::Visit(BoolType* n) {}
void TypeChecker::Visit(VoidType* n) {}


/* ---------- Helpers ---------- */

void TypeChecker::AddToFunctionTable(std::shared_ptr<FunctionDecl> n) {
    auto type = make_shared<FunctionType>();
    for (const auto& formal : n->GetFormals()) {
        type->AddParamType(formal->GetType()->GetValue());
    }
    type->SetReturnType(n->GetReturnType()->GetValue());
    symbolTable_.PutFunction(n->GetId()->GetName(), type.get());
}

void TypeChecker::Check(Expression* e, Type type) {
    // Error Handling
    // TODO: Finish Implementation
}


void TypeChecker::HandleDuplicateNameDecl(const std::string name) {
    // Error Handling
    // TODO: Finish Implementation
}