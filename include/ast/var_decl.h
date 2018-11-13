#pragma once

#include "statement.h"
#include "static_type.h"

class VarDecl : public Statement 
{
	typedef std::shared_ptr<Identifier> IdPtr;
	typedef std::shared_ptr<StaticType> TypePtr;
public:
	VarDecl() = default; 
	~VarDecl() override = default;

	void Accept(IVisitor* v) override                       {   v->Visit(this); }
	std::string ToString() override                         {   return type_->ToString() + " "
                                                                       + id_->ToString() + ";"; }

	void SetType(TypePtr type)                              {   type_ = std::move(type); }
	void SetId(IdPtr id)                                    {   id_ = std::move(id); }
	StaticType* GetType() const                             {   return type_.get(); }
	Identifier* GetId() const                               {   return id_.get(); }
private:
	TypePtr type_; 
	IdPtr id_;

}; // class VarDecl