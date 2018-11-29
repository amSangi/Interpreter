#pragma once

#include <vector>
#include "function_param.h"
#include "statement.h"
#include "static_type.h"
#include "var_decl.h"
#include "identifier.h"

class FunctionDecl : public ASTNode
{
	typedef std::shared_ptr<Identifier> IdPtr;
	typedef std::shared_ptr<FunctionParam> ParamPtr;
	typedef std::shared_ptr<Statement> StmPtr;
	typedef std::shared_ptr<StaticType> TypePtr;
public:
	FunctionDecl() = default; 
	~FunctionDecl() override = default;

	VisitorValue Accept(IVisitor* v) override                  	{   return v->Visit(this); }
	std::string ToString() override {
		std::string res = return_type_->ToString() + " " + id_->ToString() + "(";
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

	void SetReturnType(TypePtr type)                            {   return_type_ = std::move(type); }
	void SetId(IdPtr id)                                        {   id_ = std::move(id); }
	void AddFormal(ParamPtr var)                                {   formals_.emplace_back(std::move(var)); }
	void AddStm(StmPtr stm)                                     {   statements_.emplace_back(std::move(stm)); }

	TypePtr GetReturnType() const                               {   return return_type_; }
	IdPtr GetId() const                                         {   return id_; }
	const std::vector<ParamPtr>& GetFormals() const             {   return formals_; }
	const std::vector<StmPtr>& GetStatements() const            {   return statements_; }
private:
	TypePtr return_type_;
	IdPtr id_;
	std::vector<ParamPtr> formals_;
	std::vector<StmPtr> statements_;

}; // class FunctionDecl

