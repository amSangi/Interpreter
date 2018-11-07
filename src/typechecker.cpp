#include <utility>
#include "visitor/typechecker.h"
#include "function_type.h"

CheckedProgram TypeChecker::Check(std::shared_ptr<Program> program){
    program->Accept(this);
    return CheckedProgram(std::move(program), symbolTable_);
}

void TypeChecker::Visit(Program* n) {
    for (auto& fun_decl : n->GetFunctions()) {
        fun_decl->Accept(this);
    }
    n->GetMain()->Accept(this);
}


/* ---------- Functions ---------- */
void TypeChecker::Visit(FunctionDecl* n) {

}

void TypeChecker::Visit(MainFunction* n) {

}

void TypeChecker::Visit(FunctionParam* n) {

}

void TypeChecker::Visit(FunctionType* n) {

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