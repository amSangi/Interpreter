#include <sstream>
#include <iostream>
#include "parser.h"

using std::make_shared;
using std::shared_ptr;
using std::vector; 
using std::string; 

Parser::Parser(Lexer& lexer)
	: lexer_(lexer), 
	current_token_(lexer.GetNext()),
	next_token_(lexer_.GetNext()) {}


shared_ptr<Program> Parser::Parse() {
	auto program = make_shared<Program>();

	// Parse function declarations
	while (next_token_.GetType() != MainKeyword) {
		program->AddFuncDecl(ConsumeFunctionDecl());
	}

	program->SetMain(ConsumeMain());

	Expect(EndOfFileToken);
	return program;
}


const vector<string>& Parser::GetErrors() const {
	return errors_;
}

/*********** Functions ***********/
shared_ptr<FunctionDecl> Parser::ConsumeMain() {
	auto main = make_shared<FunctionDecl>();

	Expect(NumberKeyword);
	main->SetReturnType(make_shared<NumType>());

	Expect(MainKeyword);
	main->SetId(make_shared<Identifier>("main"));

	Expect(OpenParanToken);
	Expect(CloseParanToken);
	Expect(OpenBraceToken);

	// Parse statements
	while (current_token_.GetType() != CloseBraceToken
			&& current_token_.GetType() != EndOfFileToken) {
		main->AddStm(ConsumeStatement());
	}

	Expect(CloseBraceToken);
	return main;
}

shared_ptr<FunctionDecl> Parser::ConsumeFunctionDecl() {
	auto fun_decl = make_shared<FunctionDecl>();
	auto type = ConsumeStaticType();
	fun_decl->SetReturnType(type);
	fun_decl->SetId(ConsumeIdentifier());

	Expect(OpenParanToken);

	// Parse formal arguments
	while (current_token_.GetType() == BoolKeyword
           || current_token_.GetType() == VoidKeyword
           || current_token_.GetType() == NumberKeyword) {
		fun_decl->AddFormal(ConsumeFunctionParam());
		if (current_token_.GetType() == CommaToken) {
		    NextToken();
		}
	}

	Expect(CloseParanToken);
	Expect(OpenBraceToken);

	// Parse statements
	while (current_token_.GetType() != CloseBraceToken) {
		fun_decl->AddStm(ConsumeStatement());
	}

	Expect(CloseBraceToken);
	return fun_decl; 
}

shared_ptr<FunctionParam> Parser::ConsumeFunctionParam() {
	auto param = make_shared<FunctionParam>();

	param->SetType(ConsumeStaticType());
	param->SetName(ConsumeIdentifier());

	return param;
}

/*********** Statements ***********/
shared_ptr<Statement> Parser::ConsumeStatement() {
	shared_ptr<Statement> stm;

	switch (current_token_.GetType()) {
	case OpenBraceToken:
		stm = ConsumeBlock();
		break;
	case IfKeyword:
		stm = ConsumeIf();
		break;
	case WhileKeyword:
		stm = ConsumeWhile();
		break;
	case NumberKeyword:
		stm = ConsumeVarDecl();
		Expect(SemiColonToken); 
		break;
	case BoolKeyword:
		stm = ConsumeVarDecl();
		Expect(SemiColonToken); 
		break;
	case ReturnKeyword:
		stm = ConsumeReturnStm();
		Expect(SemiColonToken); 
		break;
	case IdentifierToken:
		stm = ConsumeAssignment();
		Expect(SemiColonToken); 
		break;
	default:
		return nullptr; 
	}

	return stm;
}

shared_ptr<Block> Parser::ConsumeBlock() {
	auto block = make_shared<Block>();

	Expect(OpenBraceToken); 
	
	while (current_token_.GetType() != CloseBraceToken) {
		block->AddStatement(ConsumeStatement());
	}

	Expect(CloseBraceToken); 

	return block; 
}

shared_ptr<ReturnStm> Parser::ConsumeReturnStm() {
	auto return_stm = make_shared<ReturnStm>();

	Expect(ReturnKeyword);

	if (current_token_.GetType() != SemiColonToken) {
        return_stm->SetExpression(ConsumeExpression());
    }

	return return_stm; 
}

shared_ptr<IfThenElse> Parser::ConsumeIf() {
	auto if_then_else = make_shared<IfThenElse>();

	Expect(IfKeyword); 
	Expect(OpenParanToken); 

	if_then_else->SetPredicate(ConsumeExpression());

	Expect(CloseParanToken); 
	
	// Parse then block
	if_then_else->SetThen(ConsumeBlock());

	// Parse else block - if one exists
	if (Accept(ElseKeyword)) {
		if_then_else->SetElse(ConsumeBlock());
	}

	return if_then_else; 
}

shared_ptr<While> Parser::ConsumeWhile() {
	auto while_node = make_shared<While>();

	Expect(WhileKeyword); 
	Expect(OpenParanToken);
	// Parse predicate
	while_node->SetPredicate(ConsumeExpression());
	Expect(CloseParanToken);
	while_node->SetBlock(ConsumeBlock());

	return while_node; 
}

shared_ptr<VarDecl> Parser::ConsumeVarDecl() {
	auto var_decl = make_shared<VarDecl>();

	var_decl->SetType(ConsumeStaticType());
	var_decl->SetId(ConsumeIdentifier());

	return var_decl; 
}

shared_ptr<Assignment> Parser::ConsumeAssignment() {
	auto assign = make_shared<Assignment>();

	auto id = ConsumeIdentifier();
	Expect(EqualToken); 
	auto exp = ConsumeExpression();

	assign->SetLValue(id);
	assign->SetRValue(exp);

	return assign; 
}

/*********** Expressions ***********/
shared_ptr<Expression> Parser::ConsumeExpression() {
    return ConsumeAndOrExpression();
}

shared_ptr<Expression> Parser::ConsumeAndOrExpression() {
	auto and_or = make_shared<BinaryOp>();
	auto left_exp = ConsumeComparison();

    bool is_and = current_token_.GetType() == DoubleAmpersandToken;
    bool is_or = current_token_.GetType() == DoubleBarToken;
    if (!is_and && !is_or) return left_exp;
    and_or->SetOperator(AND);
    if (is_or) and_or->SetOperator(OR);

    NextToken(); // && ||

	and_or->SetLeft(left_exp);
	and_or->SetRight(ConsumeExpression());
	and_or->SetType(make_shared<BoolType>());

	return and_or; 
}

shared_ptr<Expression> Parser::ConsumeComparison() {
    auto comp = make_shared<BinaryOp>();
    auto left_exp = ConsumeConditional();

    switch (current_token_.GetType()) {
        case GreaterThanToken:
            comp->SetOperator(GT);
            break;
        case GreaterThanEqualToken:
            comp->SetOperator(GTE);
            break;
        case EqualEqualToken:
            comp->SetOperator(EQ);
            break;
        case LessThanToken:
            comp->SetOperator(LT);
            break;
        case LessThanEqualToken:
            comp->SetOperator(LTE);
            break;
        default:
            return left_exp;
    }

    NextToken(); // > >= == < <=

    comp->SetLeft(left_exp);
    comp->SetRight(ConsumeExpression());
    comp->SetType(make_shared<BoolType>());

    return comp;
}

shared_ptr<Expression> Parser::ConsumeConditional() {
    auto conditional = make_shared<Conditional>();

    auto predicate = ConsumeAddSub();
    if (!Accept(QuestionToken)) return predicate;

    auto tval = ConsumeExpression();
    Expect(ColonToken);
    conditional->SetPredicate(predicate);
    conditional->SetTrueValue(tval);
    conditional->SetFalseValue(ConsumeExpression());

    return conditional;
}

shared_ptr<Expression> Parser::ConsumeAddSub() {
	auto add_sub = make_shared<BinaryOp>();
	auto left_exp = ConsumeMultDiv();

    bool is_add = current_token_.GetType() == PlusToken;
    bool is_sub = current_token_.GetType() == MinusToken;
    if (!is_add && !is_sub) return left_exp;

	add_sub->SetOperator(PLUS);
	if (is_sub) add_sub->SetOperator(MINUS);

	NextToken(); // + -

	add_sub->SetLeft(left_exp);
	add_sub->SetRight(ConsumeExpression());
	add_sub->SetType(make_shared<NumType>());

	return add_sub;
}

shared_ptr<Expression> Parser::ConsumeMultDiv() {
	auto exp = make_shared<BinaryOp>();
	auto left_exp = ConsumePrimaryExpression();


    bool is_mul = current_token_.GetType() == AsteriskToken;
    bool is_div = current_token_.GetType() == ForwardSlashToken;
    bool is_mod = current_token_.GetType() == ModToken;
    if (!is_mul && !is_div && !is_mod) return left_exp;

	exp->SetOperator(MULTIPLY);
	if (is_div) exp->SetOperator(DIVIDE);
	if (is_mod) exp->SetOperator(MODULO);

	NextToken(); // * /

	exp->SetLeft(left_exp);
	exp->SetRight(ConsumeConditional());
	exp->SetType(make_shared<NumType>());

	return exp;
}

shared_ptr<Expression> Parser::ConsumePrimaryExpression() {

	shared_ptr<Expression> exp;

	switch (current_token_.GetType()) {
	case IdentifierToken: {
		if (next_token_.GetType() == OpenParanToken)  exp = ConsumeFunctionCall();
		else exp = ConsumeIdentifier();
		break;
	}
    case NumericLiteral: {
		exp = make_shared<NumLiteral>(std::stod(current_token_.GetValue()));
        exp->SetType(make_shared<NumType>());
        NextToken();
		break;
	}
	case TrueKeyword: {
		// true
		exp = make_shared<BooleanLiteral>(true);
		exp->SetType(make_shared<BoolType>());
		NextToken();
		break;
	}
	case FalseKeyword: {
		// false
		exp = make_shared<BooleanLiteral>(false);
        exp->SetType(make_shared<BoolType>());
        NextToken();
		break;
	}
    case ExclamationToken: {
		// !
		exp = ConsumeUnaryOp();
		break;
	}
	case OpenParanToken: {
		// (
		NextToken();
		exp = ConsumeExpression();
		Expect(CloseParanToken);
		break;
	}
	case MinusToken: {
		// Handle negatives (e.g. -3, -some_variable)
		NextToken();
		auto mult = make_shared<BinaryOp>();
		auto negative_one = make_shared<NumLiteral>(-1);
		negative_one->SetType(make_shared<NumType>());
		mult->SetLeft(negative_one);
		mult->SetOperator(MULTIPLY);
		mult->SetRight(ConsumePrimaryExpression());
		mult->SetType(make_shared<NumType>());
		exp = mult;
		break;
	}
	default:
		return nullptr; 
	}

	return exp;
}

shared_ptr<Expression> Parser::ConsumeUnaryOp() {
    Expect(ExclamationToken);
    auto unary_op = make_shared<UnaryOp>();
    unary_op->SetOp(NOT);
    unary_op->SetExpression(ConsumeExpression());
    unary_op->SetType(make_shared<BoolType>());
    return unary_op;
}

shared_ptr<FunctionCall> Parser::ConsumeFunctionCall() {
	auto call = make_shared<FunctionCall>();

	call->SetId(ConsumeIdentifier());
	Expect(OpenParanToken);
	while (current_token_.GetType() != CloseParanToken) {
		call->AddArgument(ConsumeExpression());
		if (current_token_.GetType() == CommaToken) {
		    NextToken();
		}
	}
	Expect(CloseParanToken); 

	return call; 
}

shared_ptr<Identifier> Parser::ConsumeIdentifier() {
	if (current_token_.GetType() != IdentifierToken) return nullptr;

	auto id = make_shared<Identifier>(current_token_.GetValue());
	NextToken();
	return id;
}


shared_ptr<StaticType> Parser::ConsumeStaticType() {
	shared_ptr<StaticType> type;

	switch (current_token_.GetType()) {
	case BoolKeyword:
		type = make_shared<BoolType>();
		break;
	case NumberKeyword:
		type = make_shared<NumType>();
		break; 
	case VoidKeyword:
		type = make_shared<VoidType>();
		break; 
	default:
		RecordError("Type: Expected num, bool, or void");
		return nullptr; 
	}

	NextToken(); 
	return type; 
}


/*********** Helpers ***********/
void Parser::NextToken() {
	current_token_ =  next_token_; 
	next_token_ = lexer_.GetNext(); 
}

bool Parser::Expect(TokenType token) {
	if (Accept(token)) {
		return true; 
	}

	// Attempt to recover
	NextToken();

	// Record error
	std::stringstream ss;
	ss << "Invalid token at line: " << lexer_.GetCurrentLine()
		<< " column: " << lexer_.GetCurrentColumn();
	RecordError(ss.str());

	return false; 
}

bool Parser::Accept(TokenType token) {
	if (current_token_.GetType() == token) {
		NextToken();
		return true;
	}

	return false;
}

void Parser::RecordError(const std::string message){
    errors_.emplace_back(message);
}