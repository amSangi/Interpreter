#pragma once

#include "ast.h"
#include "lexer.h"
#include "token.h"

class Parser
{
public:
	Parser(Lexer& lexer);
	~Parser() = default;

	std::shared_ptr<Program> Parse();
private:
	Lexer & lexer_;
	Token current_token_; 
	Token next_token_; 
	
	void NextToken(); 
	bool Expect(TokenType token);
	bool Accept(TokenType token); 
	void Error(const std::string msg); 

	// Program
	std::shared_ptr<FunctionDecl> GetMain();
	std::shared_ptr<FunctionDecl> GetFunctionDecl();
	
	// Statements
	std::shared_ptr<Statement> GetStatement();
	std::shared_ptr<ReturnStm> GetReturnStm();
	std::shared_ptr<Block> GetBlock();
	std::shared_ptr<IfThenElse> GetIf();
	std::shared_ptr<While> GetWhile();
	std::shared_ptr<VarDecl> GetVarDecl();
	std::shared_ptr<Assignment> GetAssignment();
	
	// Expressions
	std::shared_ptr<Expression> GetExpression();
	std::shared_ptr<Expression> GetUnaryOp();
	std::shared_ptr<Expression> GetAndOrExpression();
	std::shared_ptr<Expression> GetConditional();
	std::shared_ptr<Expression> GetAddSub();
	std::shared_ptr<Expression> GetMultDiv();
	std::shared_ptr<Expression> GetComparison();
	std::shared_ptr<Expression> GetPrimaryExpression();
	std::shared_ptr<FunctionCall> GetFunctionCall();
	std::shared_ptr<Identifier> GetIdentifier();
	
	// Type
	std::shared_ptr<StaticType> GetStaticType();


};  // class Parser