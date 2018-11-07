#pragma once

#include "program.h"
#include "symbol_table.h"
#include "static_type.h"

class CheckedProgram
{
    typedef std::shared_ptr<StaticType> TypePtr;
public:
    CheckedProgram(std::shared_ptr<Program> program, SymbolTable<TypePtr> table)
            : program_(std::move(program)), symbol_table_(table) {}

    std::shared_ptr<Program> GetProgram()                                     {   return program_; }
    SymbolTable<TypePtr> GetSymbolTable()                                     {   return symbol_table_; }

private:
    std::shared_ptr<Program> program_;
    SymbolTable<TypePtr> symbol_table_;

}; // class CheckedProgram