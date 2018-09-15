#include <cctype>
#include "utility.h"

namespace sangi {

	bool IsAlpha(char ch) {
		return std::isalpha(static_cast<unsigned char>(ch)) != 0;
	}


	bool IsSpace(char ch) {
		return std::isspace(static_cast<unsigned char>(ch)) != 0;
	}


	bool IsDigit(char ch) {
		return std::isdigit(static_cast<unsigned char>(ch)) != 0;
	}

} // namespace sangi