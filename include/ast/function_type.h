#pragma once

#include <vector>
#include "static_type.h"
#include "return_stm.h"
#include "function_param.h"

class FunctionType : public StaticType
{
    typedef std::string string;
public:
    FunctionType() = default;
    ~FunctionType() override = default;

    void Accept(IVisitor* v) override                       {   v->Visit(this); }
    string ToString() override                              {   return "function"; }

    Type GetValue() const override                          {   return type_; }
    void SetReturnType(std::shared_ptr<StaticType> type)    {   return_type_ = std::move(type); }
    StaticType* GetReturnType() const                       {   return return_type_.get(); }
    void AddParamType(Type type)                            {   param_types_.push_back(type); }
    std::vector<Type> GetParameters()                       {   return param_types_; }
private:
    Type type_ = FUNCTION;
    std::shared_ptr<StaticType> return_type_;
    std::vector<Type> param_types_;

}; // class FunctionType