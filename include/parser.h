#pragma once

#include "ast.h"
#include "lexer.h"
#include "token.h"

/**
 *  Create an AST tree from a stream of Tokens
 *  Note: Parser will set node types if they are trivial
 *  	e.g. 	Numeric/Boolean literals,
 *  			Mathematical expressions,
 *  			Variable declarations,
 *  			Comparisons
 */
class Parser
{
public:
	explicit Parser(const std::string& filename);
	~Parser() = default;

	/**
	 * @brief     Parse an AST tree and return the root node
	 * @return    an instance of Program
	 */
	std::shared_ptr<Program> Parse();

	const std::vector<std::string>& GetErrors() const;

private:
	Lexer lexer_;
	Token current_token_; 
	Token next_token_;
	std::vector<std::string> errors_;
	
	void NextToken(); 
	bool Expect(TokenType token);
	bool Accept(TokenType token); 

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

	void RecordError(const std::string message);

};  // class Parser