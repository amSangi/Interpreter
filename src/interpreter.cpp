#include "visitor/interpreter.h"

int Interpreter::Evaluate(std::shared_ptr<Program> program) {
    return 0;
}

void Interpreter::Visit(Program* n) {

}

/*********** Statements ***********/
void Interpreter::Visit(Assignment* n) {

}

void Interpreter::Visit(Block* n) {

}

void Interpreter::Visit(IfThenElse* n) {

}

void Interpreter::Visit(While* n) {

}

void Interpreter::Visit(VarDecl* n) {

}

void Interpreter::Visit(ReturnStm* n) {

}

/*********** Functions ***********/
void Interpreter::Visit(FunctionDecl* n) {

}

void Interpreter::Visit(MainFunction* n) {

}

void Interpreter::Visit(FunctionParam* n) {

}

/*********** Expressions ***********/
void Interpreter::Visit(Identifier* n) {

}

void Interpreter::Visit(BinaryOp* n) {

}

void Interpreter::Visit(UnaryOp* n) {

}

void Interpreter::Visit(FunctionCall* n) {

}

void Interpreter::Visit(Conditional* n) {

}

void Interpreter::Visit(NumLiteral* n) {

}

void Interpreter::Visit(BooleanLiteral* n) {

}

/*********** Types ***********/
void Interpreter::Visit(NumType* n) {

}

void Interpreter::Visit(BoolType* n) {

}

void Interpreter::Visit(VoidType* n) {

}