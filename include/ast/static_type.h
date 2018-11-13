#pragma once

#include <string>
#include "ast_node.h"

enum Type {
	NUMBER,
	BOOL,
	VOID,
	FUNCTION
}; // enum Type

class StaticType : public ASTNode
{
public:
	static std::string TypeToString(Type type) {
		switch (type) {
			case NUMBER:
				return "NUMBER";
			case BOOL:
				return "BOOL";
			case VOID:
				return "VOID";
			case FUNCTION:
				return "FUNCTION";
		}
		return "UNKNOWN TYPE";
	}
	virtual Type GetValue() const = 0; 

}; // class StaticType

