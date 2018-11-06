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

    T Get(string symbol) const {
        table t = tables_.top().find(symbol);
        auto it = t.find(symbol);
        if (it == t.end()) return nullptr;
        return it->second;
    }

private:
    std::stack<table> tables_;

}; // class SymbolTable
