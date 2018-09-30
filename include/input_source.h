#pragma once

#include <utility>
#include <fstream>

/***
*	An std::ifstream wrapper to handle lookaheads, retrieval of next characters,
*	column/line references, and EndOfFile checks.
*
*	Warning: Column/Line tracking is not thread safe.
*	That is, multiple InputSources using the same ifstream may not have the corrent
*	line/column values.
*/
class InputSource
{
public:
    InputSource(std::string file_name) : input_(file_name) {}
    ~InputSource() = default;

    friend void swap(InputSource& first, InputSource& second) {
        using std::swap;

        swap(first.input_, second.input_);
        swap(first.line_, second.line_);
        swap(first.column_, second.column_);
    }

    char GetNextChar();
    void ConsumeNext();
    void SkipWhiteSpaceAndNewLines();

    char LookAheadOne();
    bool IsEndOfFile();
    size_t GetCurrentLine() const;
    size_t GetCurrentColumn() const;

private:
    std::ifstream input_;
    size_t line_ = 1;
    size_t column_ = 1;

}; // class InputSource
