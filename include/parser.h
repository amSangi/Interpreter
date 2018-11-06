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

	/*********** Functions ***********/
	std::shared_ptr<FunctionDecl> ConsumeMain();
	std::shared_ptr<FunctionDecl> ConsumeFunctionDecl();
	std::shared_ptr<FunctionParam> ConsumeFunctionParam();

	/*********** Statements ***********/
	std::shared_ptr<Statement> ConsumeStatement();
	std::shared_ptr<ReturnStm> ConsumeReturnStm();
	std::shared_ptr<Block> ConsumeBlock();
	std::shared_ptr<IfThenElse> ConsumeIf();
	std::shared_ptr<While> ConsumeWhile();
	std::shared_ptr<VarDecl> ConsumeVarDecl();
	std::shared_ptr<Assignment> ConsumeAssignment();

	/*********** Expressions ***********/
	std::shared_ptr<Expression> ConsumeExpression();
	std::shared_ptr<Expression> ConsumeUnaryOp();
	std::shared_ptr<Expression> ConsumeAndOrExpression();
	std::shared_ptr<Expression> ConsumeConditional();
	std::shared_ptr<Expression> ConsumeAddSub();
	std::shared_ptr<Expression> ConsumeMultDiv();
	std::shared_ptr<Expression> ConsumeComparison();
	std::shared_ptr<Expression> ConsumePrimaryExpression();
	std::shared_ptr<FunctionCall> ConsumeFunctionCall();
	std::shared_ptr<Identifier> ConsumeIdentifier();

	/*********** Type ***********/
	std::shared_ptr<StaticType> ConsumeStaticType();

};  // class Parser