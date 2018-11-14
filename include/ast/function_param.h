#pragma once

#include "ast_node.h"
#include "static_type.h"
#include "identifier.h"

class FunctionParam : public ASTNode
{
    typedef std::shared_ptr<Identifier> IdPtr;
    typedef std::shared_ptr<StaticType> TypePtr;
public:
    FunctionParam() = default;
    ~FunctionParam() override = default;

    void Accept(IVisitor* v) override                       {   v->Visit(this); }
    std::string ToString() override                         {   return type_->ToString() + " "
                                                                       + id_->ToString(); }

    void SetType(TypePtr type)                              {   type_ = std::move(type); }
    void SetName(IdPtr id)                                  {   id_ = std::move(id); }
    TypePtr GetType() const                                 {   return type_; }
    IdPtr GetId() const                                     {   return id_; }
private:
    TypePtr type_;
    IdPtr id_;

}; // class FunctionParam
