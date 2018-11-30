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

	VisitorValue Accept(IVisitor* v) override               {   return v->Visit(this); }
	bool IsReturn() const override                              {   return false; }
	std::string ToString() override                         {   return type_->ToString() + " "
                                                                       + id_->ToString() + ";"; }

	void SetType(TypePtr type)                              {   type_ = std::move(type); }
	void SetId(IdPtr id)                                    {   id_ = std::move(id); }
	TypePtr GetType() const                                 {   return type_; }
	IdPtr GetId() const                                     {   return id_; }
private:
	TypePtr type_; 
	IdPtr id_;

}; // class VarDecl