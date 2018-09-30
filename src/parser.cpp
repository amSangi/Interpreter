#include "parser.h"
#include <sstream>
#include <iostream>

using std::make_shared;
using std::shared_ptr;
using std::vector; 
using std::string; 

Parser::Parser(Lexer& lexer)
	: lexer_(lexer), 
	current_token_(Token(InvalidToken)), 
	next_token_(lexer_.GetNext()) {}


shared_ptr<Program> Parser::Parse() {
	NextToken();

	auto program = make_shared<Program>();

	// Parse function declarations
	auto function_decl = GetFunctionDecl();
	while (function_decl != nullptr) {
		program->AddFuncDecl(function_decl);
		function_decl = GetFunctionDecl();
	}

	// Parse main declaration
	auto main = GetMain();
	if (main == nullptr) {
		Error("No 'main' entry point found");
	}

	program->SetMain(main);

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
	auto stm = GetStatement();
	while (stm != nullptr) {
		main->AddStm(stm);
		stm = GetStatement();
	}

	Expect(CloseBraceToken);
	return main;
}

shared_ptr<FunctionDecl> Parser::GetFunctionDecl() {
	auto fun_decl = make_shared<FunctionDecl>();
	
	if (next_token_.GetType() == MainKeyword) return nullptr; 

	auto type = GetStaticType(); 
	fun_decl->SetReturnType(type);

	Expect(IdentifierToken);
	fun_decl->SetName(current_token_.GetValue()); 

	Expect(OpenParanToken);

	// Parse formal arguments
	auto var_decl = GetVarDecl(); 
	while (var_decl != nullptr) {
		fun_decl->AddFormal(var_decl);
		var_decl = GetVarDecl(); 
	}

	Expect(CloseParanToken);
	Expect(OpenBraceToken);

	// Parse statements
	auto stm = GetStatement();
	while (stm != nullptr) {
		fun_decl->AddStm(stm);
		stm = GetStatement();
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
	
	// Parse statements within block
	auto stm = GetStatement(); 
	while (stm != nullptr) {
		block->AddStatement(stm);
		stm = GetStatement(); 
	}

	Expect(CloseBraceToken); 

	return block; 
}


shared_ptr<ReturnStm> Parser::GetReturnStm() {
	auto return_stm = make_shared<ReturnStm>();

	auto exp = GetExpression(); 
	if (exp == nullptr) return nullptr;

	return_stm->SetExpression(exp);

	return return_stm; 
}


shared_ptr<IfThenElse> Parser::GetIf() {
	auto if_then_else = make_shared<IfThenElse>();

	Expect(IfKeyword); 
	Expect(OpenParanToken); 

	auto predicate = GetExpression(); 
	if (predicate == nullptr) return nullptr;
	if_then_else->SetPredicate(predicate);

	Expect(CloseParanToken); 
	
	// Parse then block
	auto if_block = GetBlock(); 
	if (if_block == nullptr) return nullptr;
	if_then_else->SetThen(if_block);

	// Parse else block - if one exists
	if (Accept(ElseKeyword)) {
		auto else_block = GetBlock(); 
		if (else_block == nullptr) return nullptr;
		if_then_else->SetElse(else_block);
	}

	return if_then_else; 
}

shared_ptr<While> Parser::GetWhile() {
	auto while_node = make_shared<While>();

	Expect(WhileKeyword); 
	Expect(OpenParanToken); 

	// Parse predicate
	auto predicate = GetExpression();
	if (predicate == nullptr) return nullptr;
	while_node->SetPredicate(predicate);

	Expect(CloseParanToken); 


	// Parse block
	auto block = GetBlock(); 
	if (block == nullptr) return nullptr;
	while_node->SetBlock(block);

	return while_node; 
}

shared_ptr<VarDecl> Parser::GetVarDecl() {
	auto var_decl = make_shared<VarDecl>();
	
	auto type = GetStaticType(); 
	auto id = GetIdentifier(); 
	if (type == nullptr || id == nullptr) return nullptr;

	var_decl->SetType(type);
	var_decl->SetName(id->GetName()); 

	return var_decl; 
}

shared_ptr<Assignment> Parser::GetAssignment() {
	auto assign = make_shared<Assignment>();

	auto id = GetIdentifier(); 
	Expect(EqualToken); 
	auto exp = GetExpression(); 

	if (id == nullptr || exp == nullptr) return nullptr;

	assign->SetLValue(id->GetName()); 
	assign->SetRValue(exp);

	return assign; 
}


shared_ptr<Expression> Parser::GetExpression() {
	return GetUnaryOp(); 
}


shared_ptr<Expression> Parser::GetUnaryOp() {
	if (!Accept(ExclamationToken)) return GetAndOrExpression();

	auto unary_op = make_shared<UnaryOp>();
	unary_op->SetOp(NOT);

	// Parse expression 
	auto exp = GetAndOrExpression();
	if (exp == nullptr) return nullptr;
	unary_op->SetExpression(exp);

	return unary_op;
}


shared_ptr<Expression> Parser::GetAndOrExpression() {
	bool is_and = next_token_.GetType() == DoubleAmpersandToken; 
	bool is_or = next_token_.GetType() == DoubleBarToken; 
	if (!is_and && !is_or) return GetConditional(); 

	auto and_or = make_shared<BinaryOp>();
	and_or->SetOperator(AND);
	if (is_or) and_or->SetOperator(OR); 

	auto left_exp = GetConditional(); 
	NextToken(); 
	auto right_exp = GetConditional(); 

	and_or->SetLeft(left_exp);
	and_or->SetRight(right_exp);

	return and_or; 
}


shared_ptr<Expression> Parser::GetConditional() {
	auto conditional = make_shared<Conditional>();

	// Parse predicate
	auto predicate = GetAddSub();
	if (!Accept(QuestionToken)) return predicate; 

	// Parse true expression
	auto tval = GetAddSub();
	Expect(ColonToken);
	// Parse false expression
	auto fval = GetAddSub();

	if (predicate == nullptr || tval == nullptr || fval == nullptr) return nullptr;

	conditional->SetPredicate(predicate);
	conditional->SetTrueValue(tval);
	conditional->SetFalseValue(fval);

	return conditional;
}


shared_ptr<Expression> Parser::GetAddSub() {
	bool is_add = next_token_.GetType() == PlusToken;
	bool is_sub = next_token_.GetType() == MinusToken;
	if (!is_add && !is_sub) return GetMultDiv();

	auto add_sub = make_shared<BinaryOp>();
	add_sub->SetOperator(PLUS);
	if (is_sub) add_sub->SetOperator(MINUS);

	auto left_exp = GetMultDiv();
	NextToken();
	auto right_exp = GetMultDiv();

	add_sub->SetLeft(left_exp);
	add_sub->SetRight(right_exp);

	return add_sub;
}

shared_ptr<Expression> Parser::GetMultDiv() {
	bool is_mul = next_token_.GetType() == AsteriskToken;
	bool is_div = next_token_.GetType() == ForwardSlashToken;
	if (!is_mul && !is_div) return GetPrimaryExpression();

	auto mul_div = make_shared<BinaryOp>();
	mul_div->SetOperator(MULTIPLY);
	if (is_div) mul_div->SetOperator(DIVIDE);

	auto left_exp = GetPrimaryExpression();
	NextToken();
	auto right_exp = GetPrimaryExpression();

	mul_div->SetLeft(left_exp);
	mul_div->SetRight(right_exp);

	return mul_div;
}

shared_ptr<Expression> Parser::GetPrimaryExpression() {

	shared_ptr<Expression> exp;

	switch (current_token_.GetType()) {
	case IdentifierToken:
		if (next_token_.GetType() == OpenParanToken) exp = GetFunctionCall(); 
		else exp = GetIdentifier(); 
		break;
	case NumberKeyword:
		exp = make_shared<NumLiteral>(std::stod(current_token_.GetValue()));
		break;
	case TrueKeyword:
		exp = make_shared<BooleanLiteral>(true);
		break;
	case FalseKeyword:
		exp = make_shared<BooleanLiteral>(false);
		break;
	case OpenParanToken:
		exp = GetExpression(); 
		Expect(CloseParanToken);
		break;
	default:
		return nullptr; 
	}

	return exp; 
}

shared_ptr<FunctionCall> Parser::GetFunctionCall() {
	auto call = make_shared<FunctionCall>();

	// Parse identifier
	auto id = GetIdentifier(); 
	if (id == nullptr) return nullptr;
	call->SetName(id->GetName()); 
	Expect(OpenParanToken); 

	// Parse arguments
	auto exp = GetExpression(); 
	while (exp != nullptr) {
		call->AddArgument(exp);
		exp = GetExpression(); 
	}

	Expect(CloseParanToken); 

	return call; 
}


shared_ptr<Identifier> Parser::GetIdentifier() {
	if (current_token_.GetType() != IdentifierToken) return nullptr;

	NextToken();
	return make_shared<Identifier>(current_token_.GetValue());
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