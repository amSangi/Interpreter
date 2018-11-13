#include <utility>
#include "visitor/typechecker.h"
#include "ast.h"

using std::shared_ptr;
using std::make_shared;
using std::string;
using std::vector;

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

// Types already set by Parser
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
    shared_ptr<StaticType> type(n->GetType());
    string name = id->GetName();
    if (symbolTable_.Get(name)) HandleDuplicateNameDecl(name);
    symbolTable_.Put(name, type);
}

void TypeChecker::Visit(ReturnStm* n) {
    auto expression = n->GetExpression();
    expression->Accept(this);
    Check(expression, symbolTable_.GetFunction(current_function_name_)->GetValue());
}

/* ---------- Expressions ---------- */
void TypeChecker::Visit(Identifier* n) {
    auto type = symbolTable_.Get(n->GetName());
    if (type == nullptr) {
        HandleUndefinedIdentifier(n->GetName());
        return;
    }

    shared_ptr<StaticType> id_type(type);
    n->SetType(id_type);
}

void TypeChecker::Visit(BinaryOp* n) {
    auto left_value = n->GetLeft();
    auto right_value = n->GetRight();

    left_value->Accept(this);
    right_value->Accept(this);

    Type type = n->GetType()->GetValue();
    Check(left_value, type);
    Check(right_value, type);
}

void TypeChecker::Visit(UnaryOp* n) {
    auto expression = n->GetExpression();
    expression->Accept(this);
    Check(expression, n->GetType()->GetValue());
}

void TypeChecker::Visit(FunctionCall* n) {
    auto function_id = n->GetId();
    shared_ptr<StaticType> type = symbolTable_.GetFunction(function_id->GetName());

    if (type == nullptr) {
        HandleUndefinedIdentifier(function_id->GetName());
        return;
    }

    // Set call type to be return type of function
    shared_ptr<FunctionType> function_type = std::dynamic_pointer_cast<FunctionType>(type);
    shared_ptr<StaticType> call_type(function_type->GetReturnType());
    n->SetType(call_type);

    // Check argument types
    for (const auto& argument : n->GetArguments()) {
        argument->Accept(this);
    }

    // Check argument/parameter match
    CheckParameterArgumentMatch(n->GetArguments(), function_type->GetParameters());
}

void TypeChecker::Visit(Conditional* n) {
    auto predicate = n->GetPredicate();
    auto true_exp = n->GetTrueValue();
    auto false_exp = n->GetFalseValue();

    predicate->Accept(this);
    Check(predicate, BOOL);

    true_exp->Accept(this);
    false_exp->Accept(this);

    // True/False expressions have the same type
    Check(true_exp, false_exp->GetType()->GetValue());
    shared_ptr<StaticType> type(true_exp->GetType());
    n->SetType(type);
}

// Types already set by Parser
void TypeChecker::Visit(NumLiteral* n) {}
void TypeChecker::Visit(BooleanLiteral* n) {}

/* ---------- Types ---------- */

// Trivial --Do nothing
void TypeChecker::Visit(NumType* n) {}
void TypeChecker::Visit(BoolType* n) {}
void TypeChecker::Visit(VoidType* n) {}


/* ---------- Helpers ---------- */

void TypeChecker::AddToFunctionTable(std::shared_ptr<FunctionDecl> n) {
    auto type = make_shared<FunctionType>();
    for (const auto& formal : n->GetFormals()) {
        type->AddParamType(formal->GetType()->GetValue());
    }
    shared_ptr<StaticType> return_type(n->GetReturnType());
    type->SetReturnType(return_type);
    symbolTable_.PutFunction(n->GetId()->GetName(), type);
}

void TypeChecker::Check(Expression* e, Type type) {
    // Error Handling
    // TODO: Finish Implementation
}


void TypeChecker::HandleDuplicateNameDecl(const std::string name) {
    // Error Handling
    // TODO: Finish Implementation
}

void TypeChecker::HandleUndefinedIdentifier(const std::string name) {
    // Error Handling
    // TODO: Finish Implementation
}

void TypeChecker::CheckParameterArgumentMatch(std::vector<TypeChecker::ExpPtr> arguments,
                                              std::vector<Type> parameter_types) {

    // TODO: Update size equality check -- error handling
    assert(arguments.size() == parameter_types.size());

    for (int i = 0; i < arguments.size(); ++i) {
        Check(arguments[i].get(), parameter_types[i]);
    }
}