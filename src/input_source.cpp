#include "input_source.h"
#include "utility.h"

using namespace sangi; 


char InputSource::GetNextChar() {
	char c;
	input_.get(c);
	++column_;
	if (c == '\n') {
		column_ = 1;
		++line_;
	}
	return c;
}


char InputSource::LookAheadOne() {
	return static_cast<char>(input_.peek());
}


bool InputSource::IsEndOfFile() {
	return input_.peek() < 0;
}


void InputSource::ConsumeNext() {
	GetNextChar();
}


void InputSource::SkipWhiteSpaceAndNewLines() {
	while (!IsEndOfFile() && IsSpace(LookAheadOne())) {
		ConsumeNext();
	}
}


size_t InputSource::GetCurrentLine() const {
	return line_; 
}


size_t InputSource::GetCurrentColumn() const {
	return column_; 
}
