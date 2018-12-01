#include "visitor/evaluator.h"
#include "ast.h"

using std::vector;
using std::string;
using std::shared_ptr;

double Evaluator::Evaluate(CheckedProgram checked_program) {
  evaluation_table_.EnterScope();
  VisitorValue main_value = checked_program.GetProgram()->Accept(this);
  evaluation_table_.LeaveScope();
  return main_value.double_value;
}

VisitorValue Evaluator::Visit(Program *n) {
  for (auto fun : n->GetFunctions()) {
    function_table_.insert({fun->GetId()->GetName(), fun});
  }

  return n->GetMain()->Accept(this);
}

/*********** Functions ***********/
VisitorValue Evaluator::Visit(FunctionDecl *n) {
  is_return_ = false;
  VisitorValue value;
  for (const auto &stm : n->GetStatements()) {
    value = stm->Accept(this);
    if (is_return_) return value;
  }

  return value;
}

VisitorValue Evaluator::Visit(FunctionParam *n) {
  return VisitorValue(); // return not needed
}


/*********** Statements ***********/
VisitorValue Evaluator::Visit(Assignment *n) {
  string name = n->GetLValue()->GetName();
  VisitorValue value = n->GetRValue()->Accept(this);
  evaluation_table_.Set(name, value);
  return VisitorValue(); // return not needed
}

VisitorValue Evaluator::Visit(Block *n) {
  for (const auto &stm : n->GetStatements()) {
    VisitorValue value = stm->Accept(this);
    if (is_return_) return value;
  }

  return VisitorValue();
}

VisitorValue Evaluator::Visit(IfThenElse *n) {
  VisitorValue predicate = n->GetPredicate()->Accept(this);

  return predicate.bool_value ? n->GetThenStatement()->Accept(this) : n->GetElseStatement()->Accept(this);
}

VisitorValue Evaluator::Visit(While *n) {
  while (n->GetPredicate()->Accept(this).bool_value) {
    VisitorValue value = n->GetBlock()->Accept(this);
    if (is_return_) return value;
  }

  return VisitorValue(); // return not needed
}

VisitorValue Evaluator::Visit(VarDecl *n) {
  evaluation_table_.Put(n->GetId()->GetName(), VisitorValue(0.0));
  return VisitorValue(); // return not needed
}

VisitorValue Evaluator::Visit(ReturnStm *n) {
  VisitorValue value = n->GetExpression()->Accept(this);
  is_return_ = true;
  return value;
}

/*********** Expressions ***********/
VisitorValue Evaluator::Visit(Identifier *n) {
  VisitorValue id_value = evaluation_table_.Get(n->GetName());
  return id_value;
}

VisitorValue Evaluator::Visit(BinaryOp *n) {
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
      return VisitorValue((double) ((long) left.double_value % (long) right.double_value));
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

VisitorValue Evaluator::Visit(UnaryOp *n) {
  VisitorValue value = n->GetExpression()->Accept(this);
  switch (n->GetOperator()) {
    case NOT:
      return VisitorValue(!(value.bool_value));
  }
  return VisitorValue(false);
}

VisitorValue Evaluator::Visit(FunctionCall *n) {
  FunDeclPtr fun = function_table_[n->GetId()->GetName()];


  // Map Arguments to Parameters
  vector<shared_ptr<Expression>> arguments = n->GetArguments();
  vector<shared_ptr<FunctionParam>> parameters = fun->GetFormals();
  std::unordered_map<string, VisitorValue> param_arg_map;

  bool prev = is_return_;
  for (int i = 0; i < arguments.size(); ++i) {
    auto arg = arguments[i];
    auto param = parameters[i];
    auto p = make_pair(param->GetId()->GetName(), arg->Accept(this));
    param_arg_map.insert(p);
    is_return_ = prev;
  }

  // Add arguments to new scope
  evaluation_table_.EnterScope();
  for (const auto& p : param_arg_map) {
    evaluation_table_.Put(p.first, p.second);
  }

  // Execute function
  VisitorValue call_value = fun->Accept(this);
  is_return_ = prev;

  evaluation_table_.LeaveScope();

  return call_value;
}

VisitorValue Evaluator::Visit(Conditional *n) {
  VisitorValue predicate = n->GetPredicate()->Accept(this);
  return predicate.bool_value ? n->GetTrueValue()->Accept(this) : n->GetFalseValue()->Accept(this);
}

VisitorValue Evaluator::Visit(NumLiteral *n) {
  return VisitorValue(n->GetValue());
}

VisitorValue Evaluator::Visit(BooleanLiteral *n) {
  return VisitorValue(n->GetValue());
}

/*********** Types ***********/
VisitorValue Evaluator::Visit(NumType *n) {
  return VisitorValue(); // return not needed
}

VisitorValue Evaluator::Visit(BoolType *n) {
  return VisitorValue(); // return not needed
}

VisitorValue Evaluator::Visit(VoidType *n) {
  return VisitorValue(); // return not needed
}

VisitorValue Evaluator::Visit(FunctionType *n) {
  return VisitorValue(); // return not needed
}