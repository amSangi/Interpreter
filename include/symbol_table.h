#pragma once

#include <unordered_map>
#include <stack>
#include <string>

template<class T>
class SymbolTable
{
    typedef std::string string;
    typedef std::unordered_map<string, T> table;
public:
    SymbolTable() = default;
    ~SymbolTable() = default;

    /*********** Scope ***********/
    void EnterScope()                                  { tables_.push(table()); }
    void LeaveScope()                                  { tables_.pop(); }

    /*********** Symbol ***********/
    void Put(string symbol, T value)                   { tables_.top()[symbol] = value; }
    void PutFunction(string symbol, T value)           { function_table_[symbol] = value; }

    T Get(const string& symbol) const                  { return GetSymbol(symbol, tables_.top()); }

    T GetFunction(const string& symbol) const          { return GetSymbol(symbol, function_table_); }

private:
    std::stack<table> tables_;
    table function_table_;


    T GetSymbol(const string& symbol, const table& t) const {
        auto it = t.find(symbol);
        if (it == t.end()) return nullptr;
        return it->second;
    }

}; // class SymbolTable
