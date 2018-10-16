#pragma once

#include <memory>

class Program; 
class Assignment; 
class Block; 
class IfThenElse; 
class While; 
class VarDecl;
class FunctionDecl;
class FunctionParam;
class MainFunction; 
class Identifier; 
class BinaryOp; 
class UnaryOp; 
class FunctionCall; 
class Conditional; 
class NumLiteral;
class BooleanLiteral; 
class NumType; 
class BoolType; 
class VoidType; 
class ReturnStm; 


class IVisitor
{
public:
	virtual ~IVisitor() = 0; 
	
	virtual void Visit(Program* n) = 0; 
	
	// Statements
	virtual void Visit(Assignment* n) = 0;
	virtual void Visit(Block* n) = 0;
	virtual void Visit(IfThenElse* n) = 0;
	virtual void Visit(While* n) = 0;
	virtual void Visit(VarDecl* n) = 0;
	virtual void Visit(ReturnStm* n) = 0; 

	// Functions
	virtual void Visit(FunctionDecl* n) = 0;
	virtual void Visit(MainFunction* n) = 0;
	virtual void Visit(FunctionParam* n) = 0;

	// Expressions
	virtual void Visit(Identifier* n) = 0;
	virtual void Visit(BinaryOp* n) = 0;
	virtual void Visit(UnaryOp* n) = 0;
	virtual void Visit(FunctionCall* n) = 0;
	virtual void Visit(Conditional* n) = 0;
	virtual void Visit(NumLiteral* n) = 0;
	virtual void Visit(BooleanLiteral* n) = 0;

	// Types
	virtual void Visit(NumType* n) = 0;
	virtual void Visit(BoolType* n) = 0;
	virtual void Visit(VoidType* n) = 0;

}; // interface IVisitor

