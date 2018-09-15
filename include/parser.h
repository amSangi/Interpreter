#pragma once

#include "lexer.h"
#include "token.h"
#include "program.h"
#include "ast.h"

class Parser
{
public:
	Parser(Lexer& lexer); 
	~Parser() = default;

	std::unique_ptr<Program> Parse();
private:
	Lexer & lexer_;
	Token current_token_; 
	Token next_token_; 
	
	void NextToken(); 
	bool Expect(TokenType token);
	bool Accept(TokenType token); 
	void Error(const std::string msg); 

	// Program
	std::unique_ptr<FunctionDecl> GetMain(); 
	std::unique_ptr<FunctionDecl> GetFunctionDecl();
	
	// Statements
	std::unique_ptr<Statement> GetStatement();
	std::unique_ptr<ReturnStm> GetReturnStm();
	std::unique_ptr<Block> GetBlock();
	std::unique_ptr<IfThenElse> GetIf();
	std::unique_ptr<While> GetWhile();
	std::unique_ptr<VarDecl> GetVarDecl();
	std::unique_ptr<Assignment> GetAssignment();
	
	// Expressions
	std::unique_ptr<Expression> GetExpression();
	std::unique_ptr<Expression> GetUnaryOp();
	std::unique_ptr<Expression> GetAndOrExpression();
	std::unique_ptr<Expression> GetConditional();
	std::unique_ptr<Expression> GetAddSub();
	std::unique_ptr<Expression> GetMultDiv();
	std::unique_ptr<Expression> GetPrimaryExpression(); 
	std::unique_ptr<FunctionCall> GetFunctionCall();
	std::unique_ptr<Identifier> GetIdentifier();
	
	// Type
	std::unique_ptr<StaticType> GetStaticType();


};  // class Parser