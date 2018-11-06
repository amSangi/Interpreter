#include "visitor/typechecker.h"

CheckedProgram TypeChecker::Check(std::shared_ptr<Program> program){
    symbolTable_.EnterScope();
    program->Accept(this);
    return CheckedProgram(program, symbolTable_);
}

void TypeChecker::Visit(Program* n) {

}

/* ---------- Statements ---------- */
void TypeChecker::Visit(Assignment* n) {

}

void TypeChecker::Visit(Block* n) {

}

void TypeChecker::Visit(IfThenElse* n) {

}

void TypeChecker::Visit(While* n) {

}

void TypeChecker::Visit(VarDecl* n) {

}

void TypeChecker::Visit(ReturnStm* n) {

}

/* ---------- Functions ---------- */
void TypeChecker::Visit(FunctionDecl* n) {

}

void TypeChecker::Visit(MainFunction* n) {

}

void TypeChecker::Visit(FunctionParam* n) {

}

/* ---------- Expressions ---------- */
void TypeChecker::Visit(Identifier* n) {

}

void TypeChecker::Visit(BinaryOp* n) {

}

void TypeChecker::Visit(UnaryOp* n) {

}

void TypeChecker::Visit(FunctionCall* n) {

}

void TypeChecker::Visit(Conditional* n) {

}

void TypeChecker::Visit(NumLiteral* n) {

}

void TypeChecker::Visit(BooleanLiteral* n) {

}

/* ---------- Types ---------- */
void TypeChecker::Visit(NumType* n) {

}

void TypeChecker::Visit(BoolType* n) {

}

void TypeChecker::Visit(VoidType* n) {

}