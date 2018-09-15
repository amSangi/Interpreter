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
    InputSource(std::ifstream& in_file);
    InputSource(const InputSource& other);
    ~InputSource();

    InputSource& operator=(InputSource other);

    friend void swap(InputSource& first, InputSource& second) {
        using std::swap;

        swap(first.input_, second.input_);
        swap(first.line_, second.line_);
        swap(first.column_, second.column_);
    }

    char GetNextChar();
    void ConsumeNext();
    void SkipWhiteSpaceAndNewLines();

    char LookAheadOne() const;
    bool IsEndOfFile() const;
    size_t GetCurrentLine() const;
    size_t GetCurrentColumn() const;

private:
    std::ifstream& input_;
    size_t line_ = 1;
    size_t column_ = 0;

}; // class InputSource
