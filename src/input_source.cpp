#include "input_source.h"
#include <fstream>
#include "utility.h"

using namespace sangi; 

InputSource::InputSource(std::ifstream& in_file)
	: input_(in_file) {}


InputSource::InputSource(const InputSource& other) = default;


InputSource::~InputSource() {
	input_.close(); 
}


InputSource& InputSource::operator=(InputSource other) {
	swap(*this, other);
	return *this;
}


char InputSource::GetNextChar() {
	char c;
	input_.get(c);
	++column_;
	if (c == '\n') {
		column_ = 0;
		++line_;
	}
	return c;
}


char InputSource::LookAheadOne() const {
	return static_cast<char>(input_.peek());
}


void InputSource::ConsumeNext() {
	GetNextChar();
}


void InputSource::SkipWhiteSpaceAndNewLines() {
	while (!IsEndOfFile() && IsSpace(LookAheadOne())) {
		ConsumeNext();
	}
}


bool InputSource::IsEndOfFile() const {
	return input_.peek() < 0;
}


size_t InputSource::GetCurrentLine() const {
	return line_; 
}


size_t InputSource::GetCurrentColumn() const {
	return column_; 
}
