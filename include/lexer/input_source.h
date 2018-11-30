#pragma once

#include <utility>
#include <fstream>

class InputSource
{
public:
  InputSource(std::string file_name) : input_(file_name) {}
  ~InputSource() = default;


  /**
   *
   * @return  The next character in the input file
   */
  char GetNextChar();

  /**
   * @brief   Skip the next character in the input file
   */
  void ConsumeNext();

  /**
   * @brief   Skip to the next non-whitespace/non-newline character
   */
  void SkipWhiteSpaceAndNewLines();

  /**
   * @return  The next character from the input file without changing position
   */
  char LookAheadOne();

  /**
   * @return  True if input_ is at the end of the file
   */
  bool IsEndOfFile();

  /**
   * @return  The current line in input_
   */
  size_t GetCurrentLine() const;

  /**
   * @return  The current column in input_
   */
  size_t GetCurrentColumn() const;

private:
  std::ifstream input_;
  size_t line_ = 1;
  size_t column_ = 1;

}; // class InputSource
