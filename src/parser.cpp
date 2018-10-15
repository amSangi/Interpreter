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
		program->AddFuncDecl(GetFunctionDecl());
	}

	program->SetMain(GetMain());

	Expect(EndOfFileToken);
	return program;
}

shared_ptr<FunctionDecl> Parser::GetMain() {
	auto main = make_shared<FunctionDecl>();

	Expect(NumberKeyword);
	main->SetReturnType(make_shared<NumType>());

	Expect(MainKeyword);
	main->SetName("main");

	Expect(OpenParanToken);
	Expect(CloseParanToken);
	Expect(OpenBraceToken);

	// Parse statements
	while (current_token_.GetType() != CloseBraceToken) {
		main->AddStm(GetStatement());
	}

	Expect(CloseBraceToken);
	return main;
}

shared_ptr<FunctionDecl> Parser::GetFunctionDecl() {
	auto fun_decl = make_shared<FunctionDecl>();
	auto type = GetStaticType(); 
	fun_decl->SetReturnType(type);

	Accept(IdentifierToken);
	fun_decl->SetName(current_token_.GetValue()); 

	Expect(OpenParanToken);

	// Parse formal arguments
	while (current_token_.GetType() == BoolKeyword
           || current_token_.GetType() == VoidKeyword
           || current_token_.GetType() == NumberKeyword) {
		fun_decl->AddFormal(GetVarDecl());
	}

	Expect(CloseParanToken);
	Expect(OpenBraceToken);

	// Parse statements
	while (current_token_.GetType() != CloseBraceToken) {
		fun_decl->AddStm(GetStatement());
	}

	Expect(CloseBraceToken);
	return fun_decl; 
}

shared_ptr<Statement> Parser::GetStatement() {
	shared_ptr<Statement> stm;

	switch (current_token_.GetType()) {
	case OpenBraceToken:
		stm = GetBlock(); 
		break;
	case IfKeyword:
		stm = GetIf(); 
		break;
	case WhileKeyword:
		stm = GetWhile(); 
		break;
	case NumberKeyword:
		stm = GetVarDecl(); 
		Expect(SemiColonToken); 
		break;
	case BoolKeyword:
		stm = GetVarDecl(); 
		Expect(SemiColonToken); 
		break;
	case ReturnKeyword:
		stm = GetReturnStm(); 
		Expect(SemiColonToken); 
		break;
	case IdentifierToken:
		stm = GetAssignment(); 
		Expect(SemiColonToken); 
		break;
	default:
		return nullptr; 
	}

	return stm;
}

shared_ptr<Block> Parser::GetBlock() {
	auto block = make_shared<Block>();

	Expect(OpenBraceToken); 
	
	while (current_token_.GetType() != CloseBraceToken) {
		block->AddStatement(GetStatement());
	}

	Expect(CloseBraceToken); 

	return block; 
}


shared_ptr<ReturnStm> Parser::GetReturnStm() {
	auto return_stm = make_shared<ReturnStm>();

	Expect(ReturnKeyword);

	if (current_token_.GetType() != SemiColonToken) {
        return_stm->SetExpression(GetExpression());
    }

	return return_stm; 
}


shared_ptr<IfThenElse> Parser::GetIf() {
	auto if_then_else = make_shared<IfThenElse>();

	Expect(IfKeyword); 
	Expect(OpenParanToken); 

	if_then_else->SetPredicate(GetExpression());

	Expect(CloseParanToken); 
	
	// Parse then block
	if_then_else->SetThen(GetBlock());

	// Parse else block - if one exists
	if (Accept(ElseKeyword)) {
		if_then_else->SetElse(GetBlock());
	}

	return if_then_else; 
}

shared_ptr<While> Parser::GetWhile() {
	auto while_node = make_shared<While>();

	Expect(WhileKeyword); 
	Expect(OpenParanToken);
	// Parse predicate
	while_node->SetPredicate(GetExpression());
	Expect(CloseParanToken);
	while_node->SetBlock(GetBlock());

	return while_node; 
}

shared_ptr<VarDecl> Parser::GetVarDecl() {
	auto var_decl = make_shared<VarDecl>();

	var_decl->SetType(GetStaticType());
	var_decl->SetName(GetIdentifier()->GetName());

	return var_decl; 
}

shared_ptr<Assignment> Parser::GetAssignment() {
	auto assign = make_shared<Assignment>();

	auto id = GetIdentifier(); 
	Expect(EqualToken); 
	auto exp = GetExpression();

	assign->SetLValue(id->GetName()); 
	assign->SetRValue(exp);

	return assign; 
}


shared_ptr<Expression> Parser::GetExpression() {
    return GetAndOrExpression();
}

shared_ptr<Expression> Parser::GetAndOrExpression() {
	auto and_or = make_shared<BinaryOp>();
	auto left_exp = GetConditional();

    bool is_and = current_token_.GetType() == DoubleAmpersandToken;
    bool is_or = current_token_.GetType() == DoubleBarToken;
    if (!is_and && !is_or) return left_exp;
    and_or->SetOperator(AND);
    if (is_or) and_or->SetOperator(OR);

    NextToken(); // && ||

	and_or->SetLeft(left_exp);
	and_or->SetRight(GetExpression());

	return and_or; 
}


shared_ptr<Expression> Parser::GetConditional() {
	auto conditional = make_shared<Conditional>();

	// Parse predicate
	auto predicate = GetAddSub();
	if (!Accept(QuestionToken)) return predicate; 

	auto tval = GetExpression();
	Expect(ColonToken);
	conditional->SetPredicate(predicate);
	conditional->SetTrueValue(tval);
	conditional->SetFalseValue(GetExpression());

	return conditional;
}


shared_ptr<Expression> Parser::GetAddSub() {
	auto add_sub = make_shared<BinaryOp>();
	auto left_exp = GetMultDiv();

    bool is_add = current_token_.GetType() == PlusToken;
    bool is_sub = current_token_.GetType() == MinusToken;
    if (!is_add && !is_sub) return left_exp;

	add_sub->SetOperator(PLUS);
	if (is_sub) add_sub->SetOperator(MINUS);

	NextToken(); // + -

	add_sub->SetLeft(left_exp);
	add_sub->SetRight(GetExpression());

	return add_sub;
}

shared_ptr<Expression> Parser::GetMultDiv() {
	auto exp = make_shared<BinaryOp>();
	auto left_exp = GetComparison();


    bool is_mul = current_token_.GetType() == AsteriskToken;
    bool is_div = current_token_.GetType() == ForwardSlashToken;
    bool is_mod = current_token_.GetType() == ModToken;
    if (!is_mul && !is_div && !is_mod) return left_exp;

	exp->SetOperator(MULTIPLY);
	if (is_div) exp->SetOperator(DIVIDE);
	if (is_mod) exp->SetOperator(MODULO);

	NextToken(); // * /

	exp->SetLeft(left_exp);
	exp->SetRight(GetExpression());

	return exp;
}


shared_ptr<Expression> Parser::GetComparison() {
    auto comp = make_shared<BinaryOp>();
    auto left_exp = GetPrimaryExpression();

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
    comp->SetRight(GetExpression());
	return comp;
}

shared_ptr<Expression> Parser::GetPrimaryExpression() {

	shared_ptr<Expression> exp;

	switch (current_token_.GetType()) {
	case IdentifierToken:
		if (next_token_.GetType() == OpenParanToken) exp = GetFunctionCall(); 
		else exp = GetIdentifier();
        break;
    case NumericLiteral:
        exp = make_shared<NumLiteral>(std::stod(current_token_.GetValue()));
        NextToken();
        break;
	case TrueKeyword:
		exp = make_shared<BooleanLiteral>(true);
        NextToken();
        break;
	case FalseKeyword:
		exp = make_shared<BooleanLiteral>(false);
        NextToken();
        break;
    case ExclamationToken:
        exp = GetUnaryOp();
        break;
	case OpenParanToken:
	    NextToken();
		exp = GetExpression(); 
		Expect(CloseParanToken);
		break;
	default:
		return nullptr; 
	}

	return exp;
}

shared_ptr<Expression> Parser::GetUnaryOp() {
    Expect(ExclamationToken);
    auto unary_op = make_shared<UnaryOp>();
    unary_op->SetOp(NOT);
    unary_op->SetExpression(GetExpression());

    return unary_op;
}

shared_ptr<FunctionCall> Parser::GetFunctionCall() {
	auto call = make_shared<FunctionCall>();

	call->SetName(GetIdentifier()->GetName());
	Expect(OpenParanToken);
	while (current_token_.GetType() != CloseParanToken) {
		call->AddArgument(GetExpression());
	}
	Expect(CloseParanToken); 

	return call; 
}


shared_ptr<Identifier> Parser::GetIdentifier() {
	if (current_token_.GetType() != IdentifierToken) return nullptr;

	auto id = make_shared<Identifier>(current_token_.GetValue());
	NextToken();
	return id;
}


shared_ptr<StaticType> Parser::GetStaticType() {
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
		Error("Type: Expected num, bool, or void"); 
		return nullptr; 
	}

	NextToken(); 
	return type; 
}


void Parser::NextToken() {
	current_token_ =  next_token_; 
	next_token_ = lexer_.GetNext(); 
}


bool Parser::Expect(TokenType token) {
	if (Accept(token)) {
		return true; 
	}

	// Record error
	std::stringstream ss;
	ss << "Invalid token at line: " << lexer_.GetCurrentLine()
		<< " column: " << lexer_.GetCurrentColumn();
	Error(ss.str());

	return false; 
}


bool Parser::Accept(TokenType token) {
	if (current_token_.GetType() == token) {
		NextToken();
		return true;
	}

	return false; 
}


void Parser::Error(const std::string msg) {
    std::cout << msg << std::endl;
}