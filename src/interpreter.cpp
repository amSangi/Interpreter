#include "visitor/interpreter.h"

double Interpreter::Evaluate(CheckedProgram checked_program) {
    return 0;
}

void Interpreter::Visit(Program* n) {
    // TODO: Finish Implementation
}

/*********** Functions ***********/
void Interpreter::Visit(FunctionDecl* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(FunctionParam* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(FunctionType* n) {
    // TODO: Finish Implementation
}

/*********** Statements ***********/
void Interpreter::Visit(Assignment* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(Block* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(IfThenElse* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(While* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(VarDecl* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(ReturnStm* n) {
    // TODO: Finish Implementation
}

/*********** Expressions ***********/
void Interpreter::Visit(Identifier* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(BinaryOp* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(UnaryOp* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(FunctionCall* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(Conditional* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(NumLiteral* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(BooleanLiteral* n) {
    // TODO: Finish Implementation
}

/*********** Types ***********/
void Interpreter::Visit(NumType* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(BoolType* n) {
    // TODO: Finish Implementation
}

void Interpreter::Visit(VoidType* n) {
    // TODO: Finish Implementation
}