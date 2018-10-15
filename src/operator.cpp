//
// Created by Amir Sangi on 2018-10-14.
//

#include <string>
#include "operator.h"

std::string BOpToString(BOperator op) {
    switch (op) {
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case MULTIPLY:
            return "*";
        case DIVIDE:
            return "/";
        case MODULO:
            return "%";
        case AND:
            return "&&";
        case OR:
            return "||";
        case GT:
            return ">";
        case GTE:
            return ">=";
        case LT:
            return "<";
        case LTE:
            return "<=";
        case EQ:
            return "==";
    }
    return "";
}

std::string UOpToString(UOperator op) {
    switch (op) {
        case NOT:
            return "!";
    }
    return "";
}