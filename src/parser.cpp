#include "parser.h"
#include <sstream>

using std::make_unique; 
using std::unique_ptr; 
using std::vector; 
using std::string; 

Parser::Parser(Lexer& lexer)
	: lexer_(lexer), 
	current_token_(Token(InvalidToken)), 
	next_token_(lexer_.GetNext()) {}


unique_ptr<Program> Parser::Parse() {
	NextToken(); 

	auto program = make_unique<Program>(); 

	// Parse function declarations 
	auto function_decl = GetFunctionDecl();
	while (function_decl.get() != nullptr) {
		program->AddFuncDecl(std::move(function_decl));
		function_decl = GetFunctionDecl(); 
	}

	// Parse main declaration
	auto main = GetMain(); 
	if (main.get() == nullptr) {
		Error("No 'main' entry point found"); 
	}
	program->SetMain(std::move(main)); 

	// Main must be last declaration according to EBNF 
	Expect(EndOfFileToken);
	return program; 
}

unique_ptr<FunctionDecl> Parser::GetMain() {
	auto main = make_unique<FunctionDecl>(); 

	Expect(NumberKeyword);
	main->SetReturnType(make_unique<NumType>()); 

	Expect(MainKeyword);
	main->SetName("main"); 

	Expect(OpenParanToken);
	Expect(CloseParanToken);
	Expect(OpenBraceToken);

	// Parse statements
	auto stm = GetStatement(); 
	while (stm != nullptr) {
		main->AddStm(std::move(stm)); 
		stm = GetStatement(); 
	}
	
	Expect(CloseBraceToken);
	return main; 
}

unique_ptr<FunctionDecl> Parser::GetFunctionDecl() {
	auto fun_decl = make_unique<FunctionDecl>(); 
	
	if (next_token_.GetType() == MainKeyword) return nullptr; 

	auto type = GetStaticType(); 
	fun_decl->SetReturnType(std::move(type)); 

	Expect(IdentifierToken);
	fun_decl->SetName(current_token_.GetValue()); 

	Expect(OpenParanToken);

	// Parse formal arguments
	auto var_decl = GetVarDecl(); 
	while (var_decl.get() != nullptr) {
		fun_decl->AddFormal(std::move(var_decl)); 
		var_decl = GetVarDecl(); 
	}

	Expect(CloseParanToken);
	Expect(OpenBraceToken);

	// Parse statements
	auto stm = GetStatement();
	while (stm != nullptr) {
		fun_decl->AddStm(std::move(stm));
		stm = GetStatement();
	}

	Expect(CloseBraceToken);
	return fun_decl; 
}

unique_ptr<Statement> Parser::GetStatement() {
	unique_ptr<Statement> stm; 

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

unique_ptr<Block> Parser::GetBlock() {
	auto block = make_unique<Block>(); 

	Expect(OpenBraceToken); 
	
	// Parse statements within block
	auto stm = GetStatement(); 
	while (stm != nullptr) {
		block->AddStatement(std::move(stm)); 
		stm = GetStatement(); 
	}

	Expect(CloseBraceToken); 

	return block; 
}


unique_ptr<ReturnStm> Parser::GetReturnStm() {
	auto return_stm = make_unique<ReturnStm>(); 

	auto exp = GetExpression(); 
	if (exp.get() == nullptr) return nullptr; 

	return_stm->SetExpression(std::move(exp)); 

	return return_stm; 
}


unique_ptr<IfThenElse> Parser::GetIf() {
	auto if_then_else = make_unique<IfThenElse>(); 

	Expect(IfKeyword); 
	Expect(OpenParanToken); 

	auto predicate = GetExpression(); 
	if (predicate.get() == nullptr) return nullptr; 
	if_then_else->SetPredicate(std::move(predicate)); 

	Expect(CloseParanToken); 
	
	// Parse then block
	auto if_block = GetBlock(); 
	if (if_block.get() == nullptr) return nullptr; 
	if_then_else->SetThen(std::move(if_block)); 

	// Parse else block - if one exists
	if (Accept(ElseKeyword)) {
		auto else_block = GetBlock(); 
		if (else_block.get() == nullptr) return nullptr; 
		if_then_else->SetElse(std::move(else_block)); 
	}

	return if_then_else; 
}

unique_ptr<While> Parser::GetWhile() {
	auto while_node = make_unique<While>(); 

	Expect(WhileKeyword); 
	Expect(OpenParanToken); 

	// Parse predicate
	auto predicate = GetExpression();
	if (predicate.get() == nullptr) return nullptr;
	while_node->SetPredicate(std::move(predicate)); 

	Expect(CloseParanToken); 


	// Parse block
	auto block = GetBlock(); 
	if (block.get() == nullptr) return nullptr; 
	while_node->SetBlock(std::move(block)); 

	return while_node; 
}

unique_ptr<VarDecl> Parser::GetVarDecl() {
	auto var_decl = make_unique<VarDecl>(); 
	
	auto type = GetStaticType(); 
	auto id = GetIdentifier(); 
	if (type.get() == nullptr || id.get() == nullptr) return nullptr; 

	var_decl->SetType(std::move(type)); 
	var_decl->SetName(id->GetName()); 

	return var_decl; 
}

unique_ptr<Assignment> Parser::GetAssignment() {
	auto assign = make_unique<Assignment>(); 

	auto id = GetIdentifier(); 
	Expect(EqualToken); 
	auto exp = GetExpression(); 

	if (id.get() == nullptr || exp.get() == nullptr) return nullptr; 

	assign->SetLValue(id->GetName()); 
	assign->SetRValue(std::move(exp)); 

	return assign; 
}


unique_ptr<Expression> Parser::GetExpression() {
	return GetUnaryOp(); 
}


unique_ptr<Expression> Parser::GetUnaryOp() {
	if (!Accept(ExclamationToken)) return GetAndOrExpression();

	auto unary_op = make_unique<UnaryOp>();
	unary_op->SetOp(NOT);

	// Parse expression 
	auto exp = GetAndOrExpression();
	if (exp.get() == nullptr) return nullptr;
	unary_op->SetExpression(std::move(exp));

	return unary_op;
}


unique_ptr<Expression> Parser::GetAndOrExpression() {
	bool is_and = next_token_.GetType() == DoubleAmpersandToken; 
	bool is_or = next_token_.GetType() == DoubleBarToken; 
	if (!is_and && !is_or) return GetConditional(); 

	auto and_or = make_unique<BinaryOp>();
	and_or->SetOperator(AND);
	if (is_or) and_or->SetOperator(OR); 

	auto left_exp = GetConditional(); 
	NextToken(); 
	auto right_exp = GetConditional(); 

	and_or->SetLeft(std::move(left_exp)); 
	and_or->SetRight(std::move(right_exp)); 

	return and_or; 
}


unique_ptr<Expression> Parser::GetConditional() {
	auto conditional = make_unique<Conditional>();

	// Parse predicate
	auto predicate = GetAddSub();
	if (!Accept(QuestionToken)) return predicate; 

	// Parse true expression
	auto tval = GetAddSub();
	Expect(ColonToken);
	// Parse false expression
	auto fval = GetAddSub();

	if (predicate.get() == nullptr || tval.get() == nullptr || fval.get() == nullptr) return nullptr;

	conditional->SetPredicate(std::move(predicate));
	conditional->SetTrueValue(std::move(tval));
	conditional->SetFalseValue(std::move(fval));

	return conditional;
}


unique_ptr<Expression> Parser::GetAddSub() {
	bool is_add = next_token_.GetType() == PlusToken;
	bool is_sub = next_token_.GetType() == MinusToken;
	if (!is_add && !is_sub) return GetMultDiv();

	auto add_sub = make_unique<BinaryOp>();
	add_sub->SetOperator(PLUS);
	if (is_sub) add_sub->SetOperator(MINUS);

	auto left_exp = GetMultDiv();
	NextToken();
	auto right_exp = GetMultDiv();

	add_sub->SetLeft(std::move(left_exp));
	add_sub->SetRight(std::move(right_exp));

	return add_sub;
}

unique_ptr<Expression> Parser::GetMultDiv() {
	bool is_mul = next_token_.GetType() == AsteriskToken;
	bool is_div = next_token_.GetType() == ForwardSlashToken;
	if (!is_mul && !is_div) return GetPrimaryExpression();

	auto mul_div = make_unique<BinaryOp>();
	mul_div->SetOperator(MULTIPLY);
	if (is_div) mul_div->SetOperator(DIVIDE);

	auto left_exp = GetPrimaryExpression();
	NextToken();
	auto right_exp = GetPrimaryExpression();

	mul_div->SetLeft(std::move(left_exp));
	mul_div->SetRight(std::move(right_exp));

	return mul_div;
}

unique_ptr<Expression> Parser::GetPrimaryExpression() {

	unique_ptr<Expression> exp;

	switch (current_token_.GetType()) {
	case IdentifierToken:
		if (next_token_.GetType() == OpenParanToken) exp = GetFunctionCall(); 
		else exp = GetIdentifier(); 
		break;
	case NumberKeyword:
		exp = make_unique<NumLiteral>(std::stod(current_token_.GetValue())); 
		break;
	case TrueKeyword:
		exp = make_unique<BooleanLiteral>(true); 
		break;
	case FalseKeyword:
		exp = make_unique<BooleanLiteral>(false); 
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

unique_ptr<FunctionCall> Parser::GetFunctionCall() {
	auto call = make_unique<FunctionCall>(); 

	// Parse identifier
	auto id = GetIdentifier(); 
	if (id.get() == nullptr) return nullptr; 
	call->SetName(id->GetName()); 
	Expect(OpenParanToken); 

	// Parse arguments
	auto exp = GetExpression(); 
	while (exp.get() != nullptr) {
		call->AddArgument(std::move(exp)); 
		exp = GetExpression(); 
	}

	Expect(CloseParanToken); 

	return call; 
}


unique_ptr<Identifier> Parser::GetIdentifier() {
	if (current_token_.GetType() != IdentifierToken) return nullptr;

	NextToken();
	return make_unique<Identifier>(current_token_.GetValue());
}


unique_ptr<StaticType> Parser::GetStaticType() {
	unique_ptr<StaticType> type;  

	switch (current_token_.GetType()) {
	case BoolKeyword:
		type = make_unique<BoolType>(); 
		break;
	case NumberKeyword:
		type = make_unique<NumType>(); 
		break; 
	case VoidKeyword:
		type = make_unique<VoidType>(); 
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


// TODO: Implement error handling
void Parser::Error(const std::string msg) {
	// stub
}