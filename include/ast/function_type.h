#pragma once

#include <vector>
#include "static_type.h"
#include "return_stm.h"
#include "function_param.h"

class FunctionType : public StaticType
{
    typedef std::string string;
    typedef std::shared_ptr<StaticType> TypePtr;
public:
    FunctionType() = default;
    ~FunctionType() override = default;

    VisitorValue Accept(IVisitor* v) override               {   return v->Visit(this); }
    string ToString() override                              {   return "function"; }

    Type GetValue() const override                          {   return type_; }
    void SetReturnType(TypePtr type)                        {   return_type_ = std::move(type); }
    TypePtr GetReturnType() const                           {   return return_type_; }

    void AddParamType(Type type)                            {   param_types_.push_back(type); }
    std::vector<Type> GetParameters()                       {   return param_types_; }
private:
    Type type_ = FUNCTION;
    TypePtr return_type_;
    std::vector<Type> param_types_;

}; // class FunctionType