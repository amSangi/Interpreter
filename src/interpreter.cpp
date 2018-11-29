#include "visitor/interpreter.h"

double Interpreter::Evaluate(CheckedProgram checked_program) {
    typechecker_table_ = checked_program.GetSymbolTable();
    evaluation_table_.EnterScope();
    checked_program.GetProgram()->Accept(this);
    return 0.0; // stub
}

VisitorValue Interpreter::Visit(Program* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

/*********** Functions ***********/
VisitorValue Interpreter::Visit(FunctionDecl* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
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
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(BinaryOp* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(UnaryOp* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(FunctionCall* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(Conditional* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(NumLiteral* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(BooleanLiteral* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

/*********** Types ***********/
VisitorValue Interpreter::Visit(NumType* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(BoolType* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}

VisitorValue Interpreter::Visit(VoidType* n) {
    // TODO: Finish Implementation
    return VisitorValue(nullptr); // stub
}