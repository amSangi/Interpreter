#pragma once

#include <unordered_map>
#include <utility>
#include <stack>
#include <string>

template<class T>
class SymbolTable {
  typedef std::string string;
  typedef std::unordered_map<string, T> table;
public:
  SymbolTable() = default;
  explicit SymbolTable(T default_value) : default_value_(default_value) {}
  ~SymbolTable() = default;

  /*********** Scope ***********/
  void EnterScope() { tables_.push(table()); }
  void LeaveScope() { tables_.pop(); }

  /*********** Symbol ***********/
  void Put(string symbol, T value) { tables_.top().insert(std::make_pair(symbol, value)); }
  void Set(string symbol, T value) { tables_.top()[symbol] = value; }
  void PutFunction(string symbol, T value) { function_table_.insert(std::make_pair(symbol, value)); }
  T Get(const string &symbol) const { return GetSymbol(symbol, tables_.top()); }
  T GetFunction(const string &symbol) const { return GetSymbol(symbol, function_table_); }

private:
  T default_value_ = nullptr;
  std::stack<table> tables_;
  table function_table_;


  T GetSymbol(const string &symbol, const table &t) const {
    auto it = t.find(symbol);
    if (it == t.end()) return default_value_;
    return it->second;
  }

}; // class SymbolTable
