#include "visitor/interpreter.h"
#include "ast.h"

double Interpreter::Evaluate(CheckedProgram checked_program) {
    typechecker_table_ = checked_program.GetSymbolTable();
    evaluation_table_.EnterScope();
    return checked_program.GetProgram()->Accept(this).double_value;
}

VisitorValue Interpreter::Visit(Program* n) {
    functions_ = n->GetFunctions();
    return n->GetMain()->Accept(this);
}

/*********** Functions ***********/
VisitorValue Interpreter::Visit(FunctionDecl* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); 
}

VisitorValue Interpreter::Visit(FunctionParam* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(FunctionType* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

/*********** Statements ***********/
VisitorValue Interpreter::Visit(Assignment* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(Block* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(IfThenElse* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(While* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(VarDecl* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(ReturnStm* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

/*********** Expressions ***********/
VisitorValue Interpreter::Visit(Identifier* n) {
    return evaluation_table_.Get(n->GetName());
}

VisitorValue Interpreter::Visit(BinaryOp* n) {
    VisitorValue left = n->GetLeft()->Accept(this);
    VisitorValue right = n->GetRight()->Accept(this);
    switch (n->GetOperator()) {
        case PLUS:
            return VisitorValue(left.double_value + right.double_value);
        case MINUS:
            return VisitorValue(left.double_value - right.double_value);
        case MULTIPLY:
            return VisitorValue(left.double_value * right.double_value);
        case DIVIDE:
            return VisitorValue(left.double_value / right.double_value);
        case MODULO:
            return VisitorValue((double) ((long)left.double_value % (long)right.double_value));
        case AND:
            return VisitorValue(left.bool_value && right.bool_value);
        case OR:
            return VisitorValue(left.bool_value || right.bool_value);
        case GT:
            return VisitorValue(left.double_value > right.double_value);
        case GTE:
            return VisitorValue(left.double_value >= right.double_value);
        case LT:
            return VisitorValue(left.double_value < right.double_value);
        case LTE:
            return VisitorValue(left.double_value <= right.double_value);
        case EQ:
            return VisitorValue(left.double_value == right.double_value);
    }
    return VisitorValue(0.0);
}

VisitorValue Interpreter::Visit(UnaryOp* n) {
    VisitorValue value = n->GetExpression()->Accept(this);
    switch (n->GetOperator()) {
        case NOT:
            return VisitorValue(!(value.bool_value));
    }
    return VisitorValue(false);
}

VisitorValue Interpreter::Visit(FunctionCall* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(Conditional* n) {
    VisitorValue predicate = n->GetPredicate()->Accept(this);
    return predicate.bool_value ? n->GetTrueValue()->Accept(this) : n->GetFalseValue()->Accept(this);
}

VisitorValue Interpreter::Visit(NumLiteral* n) {
    return VisitorValue(n->GetValue());
}

VisitorValue Interpreter::Visit(BooleanLiteral* n) {
    return VisitorValue(n->GetValue());
}

/*********** Types ***********/
VisitorValue Interpreter::Visit(NumType* n) {
    return VisitorValue(nullptr); // Do not do anything
}

VisitorValue Interpreter::Visit(BoolType* n) {
    return VisitorValue(nullptr); // Do not do anything
}

VisitorValue Interpreter::Visit(VoidType* n) {
    return VisitorValue(nullptr); // Do not do anything
}