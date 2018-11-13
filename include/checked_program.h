#pragma once

#include "program.h"
#include "symbol_table.h"
#include "static_type.h"

class CheckedProgram
{
public:
    CheckedProgram(std::shared_ptr<Program> program, SymbolTable<StaticType*> table)
            : program_(std::move(program)), symbol_table_(table) {}

    std::shared_ptr<Program> GetProgram()                                     {   return program_; }
    SymbolTable<StaticType*> GetSymbolTable()                                 {   return symbol_table_; }

private:
    std::shared_ptr<Program> program_;
    SymbolTable<StaticType*> symbol_table_;

}; // class CheckedProgram