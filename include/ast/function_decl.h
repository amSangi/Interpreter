#pragma once

#include <string>
#include <vector>
#include "statement.h"
#include "static_type.h"
#include "var_decl.h"

class FunctionDecl : public ASTNode
{
	typedef std::string string;
	typedef std::shared_ptr<VarDecl> VarPtr;
	typedef std::shared_ptr<Statement> StmPtr;
	typedef std::shared_ptr<StaticType> TypePtr;
public:
	FunctionDecl() = default; 
	virtual ~FunctionDecl() = default;

	virtual void Accept(std::shared_ptr<IVisitor> v)			{	v->Visit(this); }
	virtual std::string ToString()								{
		std::string res = return_type_->ToString() + " " + name_ + "(";
		for (int i = 0; i < formals_.size(); ++i) {
			res += formals_[i]->ToString();
			if (i + 1 < formals_.size()) res += ", ";
		}
		res += ") {\n";
		for (auto statement : statements_) {
			res += statement->ToString();
			res += "\n";
		}
		res += "}\n";
		return res;
	}

	void SetReturnType(TypePtr type)							{	return_type_ = std::move(type); }
	void SetName(const string name)								{	name_ = name; }
	void AddFormal(VarPtr var)									{	formals_.emplace_back(std::move(var)); }
	void AddStm(StmPtr stm)										{	statements_.emplace_back(std::move(stm)); }

	StaticType* GetReturnType() const							{	return return_type_.get(); }
	string GetName() const										{	return name_; }
	const std::vector<VarPtr>& GetFormals() const				{	return formals_; }
	const std::vector<StmPtr>& GetStatements() const			{	return statements_; }
private:
	TypePtr return_type_;
	string name_;
	std::vector<VarPtr> formals_;
	std::vector<StmPtr> statements_;

}; // class FunctionDecl

