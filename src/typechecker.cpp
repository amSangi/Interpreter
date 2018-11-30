#include <sstream>
#include "visitor/typechecker.h"
#include "ast.h"

#define VOID VisitorValue(nullptr)

using std::shared_ptr;
using std::make_shared;
using std::string;
using std::vector;


CheckedProgram TypeChecker::TypeCheck(std::shared_ptr<Program> program){
    program->Accept(this);
    return CheckedProgram(std::move(program), symbolTable_);
}


const vector<string>& TypeChecker::GetErrors() const {
    return errors_;
}


VisitorValue TypeChecker::Visit(Program* n) {
    // Build function table
    for (const auto& fun_decl : n->GetFunctions()) {
        AddToFunctionTable(fun_decl);
    }
    auto main = n->GetMain();
    AddToFunctionTable(main);

    // Typecheck functions
    for (const auto& fun_decl : n->GetFunctions()) {
        symbolTable_.EnterScope();
        fun_decl->Accept(this);
        symbolTable_.LeaveScope();
    }

    // Typecheck main
    symbolTable_.EnterScope();
    main->Accept(this);
    symbolTable_.LeaveScope();

    return VOID; // visitor returns nothing
}


/* ---------- Functions ---------- */
VisitorValue TypeChecker::Visit(FunctionDecl* n) {
    current_function_name_ = n->GetId()->GetName();
    // Add formal parameters into symbol table
    for (const auto& parameter : n->GetFormals()) {
        // Types set at parse level
        symbolTable_.Put(parameter->GetId()->GetName(), parameter->GetType());
    }

    for (const auto& statement : n->GetStatements()) {
        statement->Accept(this);
    }

    return VOID; // visitor returns nothing
}

// Types already set by Parser
VisitorValue TypeChecker::Visit(FunctionParam* n) {
    return VOID; // visitor returns nothing
}

/* ---------- Statements ---------- */
VisitorValue TypeChecker::Visit(Assignment* n) {
    auto l_value = n->GetLValue();
    auto r_value = n->GetRValue();
    l_value->Accept(this);
    r_value->Accept(this);
    Check(r_value, l_value->GetType()->GetValue());
    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(Block* n) {
    for (const auto& statement : n->GetStatements()) {
        statement->Accept(this);
    }
    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(IfThenElse* n) {
    auto predicate = n->GetPredicate();
    auto then = n->GetThenStatement();
    auto els = n->GetElseStatement();
    predicate->Accept(this);
    Check(predicate, BOOL);
    then->Accept(this);
    if (els != nullptr) els->Accept(this);

    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(While* n) {
    auto predicate = n->GetPredicate();
    auto block = n->GetBlock();
    predicate->Accept(this);
    Check(predicate, BOOL);
    block->Accept(this);

    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(VarDecl* n) {
    auto id = n->GetId();
    auto type = n->GetType();
    string name = id->GetName();
    if (symbolTable_.Get(name) != nullptr) HandleDuplicateNameDecl(name);
    else symbolTable_.Put(name, type);

    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(ReturnStm* n) {
    auto expression = n->GetExpression();
    expression->Accept(this);

    auto type = symbolTable_.GetFunction(current_function_name_);
    auto function_type = std::dynamic_pointer_cast<FunctionType>(type);
    Check(expression, function_type->GetReturnType()->GetValue());

    return VOID; // visitor returns nothing
}

/* ---------- Expressions ---------- */
VisitorValue TypeChecker::Visit(Identifier* n) {
    auto type = symbolTable_.Get(n->GetName());
    if (type == nullptr) {
        HandleUndefinedIdentifier(n->GetName());
        return VOID;
    }

    n->SetType(type);

    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(BinaryOp* n) {
    auto left_value = n->GetLeft();
    auto right_value = n->GetRight();

    left_value->Accept(this);
    right_value->Accept(this);

    switch (n->GetOperator()) {
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE:
        case MODULO:
        case GT:
        case GTE:
        case LT:
        case LTE:
        case EQ:
            Check(left_value, NUMBER);
            Check(right_value, NUMBER);
            break;
        case AND:
        case OR:
            Check(left_value, BOOL);
            Check(right_value, BOOL);
            break;
    }

    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(UnaryOp* n) {
    auto expression = n->GetExpression();
    expression->Accept(this);
    Check(expression, n->GetType()->GetValue());

    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(FunctionCall* n) {
    auto function_id = n->GetId();
    auto type = symbolTable_.GetFunction(function_id->GetName());

    if (type == nullptr) {
        HandleUndefinedIdentifier(function_id->GetName());
        return VOID; // visitor returns nothing
    }

    // Set call type to be return type of function
    auto function_type = std::dynamic_pointer_cast<FunctionType>(type);
    n->SetType(function_type->GetReturnType());

    // Check argument types
    for (const auto& argument : n->GetArguments()) {
        argument->Accept(this);
    }

    // Check argument/parameter match
    CheckParameterArgumentMatch(n->GetArguments(), function_type->GetParameters());

    return VOID; // visitor returns nothing
}

VisitorValue TypeChecker::Visit(Conditional* n) {
    auto predicate = n->GetPredicate();
    auto true_exp = n->GetTrueValue();
    auto false_exp = n->GetFalseValue();

    predicate->Accept(this);
    Check(predicate, BOOL);

    true_exp->Accept(this);
    false_exp->Accept(this);

    // True/False expressions have the same type
    Check(true_exp, false_exp->GetType()->GetValue());
    n->SetType(true_exp->GetType());

    return VOID; // visitor returns nothing
}

// Parser set their types already
VisitorValue TypeChecker::Visit(NumLiteral* n) {
    return VOID; // visitor returns nothing
}
VisitorValue TypeChecker::Visit(BooleanLiteral* n) {
    return VOID; // visitor returns nothing
}

/* ---------- Types ---------- */

// Trivial -- Do nothing
VisitorValue TypeChecker::Visit(NumType* n) {
    return VOID; // visitor returns nothing
}
VisitorValue TypeChecker::Visit(BoolType* n) {
    return VOID; // visitor returns nothing
}
VisitorValue TypeChecker::Visit(VoidType* n) {
    return VOID; // visitor returns nothing
}
VisitorValue TypeChecker::Visit(FunctionType* n) {
    return VOID; // visitor returns nothing
}

/* ---------- Helpers ---------- */

void TypeChecker::AddToFunctionTable(shared_ptr<FunctionDecl> n) {
    auto type = make_shared<FunctionType>();
    for (const auto& formal : n->GetFormals()) {
        type->AddParamType(formal->GetType()->GetValue());
    }
    type->SetReturnType(n->GetReturnType());
    symbolTable_.PutFunction(n->GetId()->GetName(), type);
}

void TypeChecker::Check(ExpPtr e, Type type) {
    if (e->GetType() == nullptr) RecordError("Type has not been set");
    else if (e->GetType()->GetValue() != type) {
        std::stringstream ss;
        ss << "EXPECTED: " << StaticType::TypeToString(type)
           << " RECEIVED: " << StaticType::TypeToString(e->GetType()->GetValue());
        RecordError(ss.str());
    }
}


void TypeChecker::HandleDuplicateNameDecl(const string name) {
    RecordError("Duplicate name declaration: " + name);
}

void TypeChecker::HandleUndefinedIdentifier(const string name) {
    RecordError("Undefined variable: " + name);
}

void TypeChecker::CheckParameterArgumentMatch(vector<ExpPtr> arguments,
                                              vector<Type> parameter_types) {

    if (arguments.size() != parameter_types.size()) {
        RecordError("Parameter/Argument mismatch");
        return; 
    }

    for (int i = 0; i < arguments.size(); ++i) {
        Check(arguments[i], parameter_types[i]);
    }
}

void TypeChecker::RecordError(const string message) {
    errors_.emplace_back(message);
}