#pragma once

#include "ast_node.h"
#include "ivisitor.h"
#include "checked_program.h"

class Evaluator : public IVisitor {
  typedef std::shared_ptr<FunctionDecl> FunDeclPtr;
public:
  Evaluator() : evaluation_table_(VisitorValue(0.0)), is_return_(false) {}

  ~Evaluator() = default;

  /**
   * Evaluate the type checked program.
   * Throws an exception in the case of a runtime error;
   *
   * @param checked_program    the type checked program
   * @return                   the result of the main method (evaluation)
   */
  double Evaluate(CheckedProgram checked_program);

private:

  static const long kMaxCallDepth = 100;

  SymbolTable<VisitorValue> evaluation_table_;
  std::unordered_map <std::string, FunDeclPtr> function_table_;
  bool is_return_;

  VisitorValue Visit(Program *n) override;

  /*********** Functions ***********/
  VisitorValue Visit(FunctionDecl *n) override;
  VisitorValue Visit(FunctionParam *n) override;

  /*********** Statements ***********/
  VisitorValue Visit(Assignment *n) override;
  VisitorValue Visit(Block *n) override;
  VisitorValue Visit(IfThenElse *n) override;
  VisitorValue Visit(While *n) override;
  VisitorValue Visit(VarDecl *n) override;
  VisitorValue Visit(ReturnStm *n) override;

  /*********** Expressions ***********/
  VisitorValue Visit(Identifier *n) override;
  VisitorValue Visit(BinaryOp *n) override;
  VisitorValue Visit(UnaryOp *n) override;
  VisitorValue Visit(FunctionCall *n) override;
  VisitorValue Visit(Conditional *n) override;
  VisitorValue Visit(NumLiteral *n) override;
  VisitorValue Visit(BooleanLiteral *n) override;

  /*********** Types ***********/
  VisitorValue Visit(NumType *n) override;
  VisitorValue Visit(BoolType *n) override;
  VisitorValue Visit(VoidType *n) override;
  VisitorValue Visit(FunctionType *n) override;

}; // class Evaluator