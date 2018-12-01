#include <algorithm>
#include <cctype>
#include "utility.h"
#include "lexer.h"

using namespace sangi;

// Static list of reserved words in the same order they appear in TokenType
const std::vector<std::string> Lexer::kReservedWords{"if", "else", "return", "while", "true", "false", "num", "bool",
                                                     "void", "main"};


bool Lexer::FailedToOpen() const {
  return !input_.IsFileOpen();
}

size_t Lexer::GetCurrentLine() const {
  return input_.GetCurrentLine();
}


size_t Lexer::GetCurrentColumn() const {
  return input_.GetCurrentColumn();
}


Token Lexer::GetNext() {

  input_.SkipWhiteSpaceAndNewLines();
  if (input_.IsEndOfFile()) {
    return Token(EndOfFileToken);
  }
  char c = input_.GetNextChar();

  // Reserved and Valid Identifiers
  if (IsAlpha(c) || c == '_') {
    return RecognizeIdentifier(c);
  }
    // Numeric Literals
  else if (IsDigit(c)) {
    return RecognizeNumber(c);
  }
    // Punctuation and Operators
  else {
    return RecognizeSymbol(c);
  }

}

bool Lexer::HasNext() {
  return !input_.IsEndOfFile();
}


Token Lexer::RecognizeSymbol(char start) {
  std::string value;
  value += start;


  value += input_.LookAheadOne();

  if (value.length() > 2) {
    return Token(InvalidToken);
  }

  switch (value[0]) {
    case '(':
      return Token(OpenParanToken);
    case ')':
      return Token(CloseParanToken);
    case '{':
      return Token(OpenBraceToken);
    case '}':
      return Token(CloseBraceToken);
    case ',':
      return Token(CommaToken);
    case ';':
      return Token(SemiColonToken);
    case ':':
      return Token(ColonToken);
    case '?':
      return Token(QuestionToken);
    case '+':
      return Token(PlusToken);
    case '-':
      return Token(MinusToken);
    case '*':
      return Token(AsteriskToken);
    case '/':
      return Token(ForwardSlashToken);
    case '%':
      return Token(ModToken);
    case '!':
      return Token(ExclamationToken);
    case '&':
      if (value.length() == 2 && value[1] == '&') {
        input_.ConsumeNext();
        return Token(DoubleAmpersandToken);
      }
      return Token(AmpersandToken);
    case '|':
      if (value.length() == 2 && value[1] == '|') {
        input_.ConsumeNext();
        return Token(DoubleBarToken);
      }
      return Token(BarToken);
    case '<':
      if (value.length() == 2 && value[1] == '=') {
        input_.ConsumeNext();
        return Token(LessThanEqualToken);
      }
      return Token(LessThanToken);
    case '=':
      if (value.length() == 2 && value[1] == '=') {
        input_.ConsumeNext();
        return Token(EqualEqualToken);
      }
      return Token(EqualToken);
    case '>':
      if (value.length() == 2 && value[1] == '=') {
        input_.ConsumeNext();
        return Token(GreaterThanEqualToken);
      }
      return Token(GreaterThanToken);

    default:
      return Token(InvalidToken);
  }
}


Token Lexer::RecognizeIdentifier(char start) {
  std::string value;
  value += start;

  bool is_identifier = (start == '_');
  char c = input_.LookAheadOne();

  while (!input_.IsEndOfFile() && !IsEndOfStatement()) {

    // Only non-reserved words contain digits/underscores
    if (IsDigit(c) || c == '_') {
      is_identifier = true;
    } else if (!IsAlpha(c)) {
      break;
    }

    value += input_.GetNextChar();
    c = input_.LookAheadOne();
  }


  if (is_identifier) {
    return Token(IdentifierToken, value);
  }

  Token reserved = RecognizeReserved(value);
  if (reserved.GetType() == InvalidToken) {
    return Token(IdentifierToken, value);
  }

  return reserved;
}


Token Lexer::RecognizeNumber(char start) {
  std::string number;
  number += start;

  // Regex: [0-9]+ (".")? [0-9]*
  char c = input_.LookAheadOne();
  bool is_decimal = false;
  while (!input_.IsEndOfFile() && !IsEndOfStatement()) {

    if (c == '.' && !is_decimal) {
      is_decimal = true;
    } else if (!IsDigit(c)) {
      break;
    }

    number += input_.GetNextChar();
    c = input_.LookAheadOne();
  }

  return Token(NumericLiteral, number);
}


Token Lexer::RecognizeReserved(const std::string &word) {
  auto it = std::find(kReservedWords.begin(), kReservedWords.end(), word);

  if (it != kReservedWords.end()) {
    long index = std::distance(kReservedWords.begin(), it);
    switch (index) {
      case 0:
        return Token(IfKeyword);
      case 1:
        return Token(ElseKeyword);
      case 2:
        return Token(ReturnKeyword);
      case 3:
        return Token(WhileKeyword);
      case 4:
        return Token(TrueKeyword);
      case 5:
        return Token(FalseKeyword);
      case 6:
        return Token(NumberKeyword);
      case 7:
        return Token(BoolKeyword);
      case 8:
        return Token(VoidKeyword);
      case 9:
        return Token(MainKeyword);
    }
  }

  return Token(InvalidToken);
}


bool Lexer::IsEndOfStatement() {
  char c = input_.LookAheadOne();
  return IsSpace(c) || c == ';';
}