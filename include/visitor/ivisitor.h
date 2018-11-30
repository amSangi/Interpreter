#pragma once

#include <memory>
#include <cstddef>

class Program; 
class Assignment; 
class Block; 
class IfThenElse; 
class While; 
class VarDecl;
class FunctionDecl;
class FunctionParam;
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
class FunctionType;
class ReturnStm;



union VisitorValue {
    double double_value;
    void* void_value;
    bool bool_value;
    explicit VisitorValue(double val) : double_value(val) {}
	explicit VisitorValue(std::nullptr_t val) : void_value(val) {}
	explicit VisitorValue(bool val) : bool_value(val) {}
}; // union VisitorValue

class IVisitor
{
public:
	virtual VisitorValue Visit(Program* n) = 0;

	/*********** Functions ***********/
	virtual VisitorValue Visit(FunctionDecl* n) = 0;
	virtual VisitorValue Visit(FunctionParam* n) = 0;
	virtual VisitorValue Visit(FunctionType* n) = 0;

	/*********** Statements ***********/
	virtual VisitorValue Visit(Assignment* n) = 0;
	virtual VisitorValue Visit(Block* n) = 0;
	virtual VisitorValue Visit(IfThenElse* n) = 0;
	virtual VisitorValue Visit(While* n) = 0;
	virtual VisitorValue Visit(VarDecl* n) = 0;
	virtual VisitorValue Visit(ReturnStm* n) = 0;

	/*********** Expressions ***********/
	virtual VisitorValue Visit(Identifier* n) = 0;
	virtual VisitorValue Visit(BinaryOp* n) = 0;
	virtual VisitorValue Visit(UnaryOp* n) = 0;
	virtual VisitorValue Visit(FunctionCall* n) = 0;
	virtual VisitorValue Visit(Conditional* n) = 0;
	virtual VisitorValue Visit(NumLiteral* n) = 0;
	virtual VisitorValue Visit(BooleanLiteral* n) = 0;

	/*********** Types ***********/
	virtual VisitorValue Visit(NumType* n) = 0;
	virtual VisitorValue Visit(BoolType* n) = 0;
	virtual VisitorValue Visit(VoidType* n) = 0;

}; // interface IVisitor

