## About ##
A simple interpreter written in C++. The interpreter includes a hand-written lexical analyzer, LL(1) parser, and typechecker. 
Tested using the Google Test framework. 

## Features ##
- Function calls 
- Recursion
- Data Types:
  - Number
  - Boolean
- Control Flow:
  - If/Else
  - While

## Example ##
```
num add(num x, num y) {
    return x + y;
}

num div(num x, num y) {
    return x / y;
}

num mul(num x, num y) {
    return x * y;
}

num sub(num x, num y) {
    return (x - y);
}

num gcd(num x, num y) {
    if (x % y == 0) {
        return y;
    }
    else {
        return gcd(y, x % y);
    }
}

num main() {
    num x;
    num y;
    num z;
    x = sub(add(100, 100), 5);
    y = div(1500, mul(5, 3));
    z = gcd(x, y);
    while (z >= 0) {
        z = sub(z, 1);
    }
    return z + 10;
}
```

## EBNF ##
```
Program --> (Function)* MainFunction

MainFunction --> "num" "main" "(" ")" Block
Function --> Type Identifier "(" FormalList ")" Block
FormalList --> VarDecl ("," VarDecl)*

Statement --> Block | If  | While | VarDecl ";" | Assignment ";" | Return ";"
Block --> "{" (Statement)* "}"
If --> "if" "(" Expression ")" Statement "else" Statement
While --> "while" "(" Expression ")" Statement
VarDecl --> Type Identifier
Assignment --> Identifier "=" Expression
Return --> "return" Expression


Expression --> AndOrExpression
AndOrExpression --> CompExpression ( Cond Expression )?
CompExpression --> CondExpression ( Comp Expression )?
CondExpression --> AddSubExpression ( "?" Expression ":" Expression )?
AddSubExpression --> MultDivExpression ( AddSub Expression )?
MultDivExpression --> PrimaryExpression ( MulDiv CondExpression )?
PrimaryExpression -->
	Identifier
	| FunctionCall
	| NumLiteral
	| BooleanLiteral
	| NotExpression
	| "-" PrimaryExpression
	| "(" Expression ")"

NotExpression --> "!" Expression
FunctionCall --> Identifier "(" ExpressionList ")"
ExpressionList --> Expression ("," Expression)*

Type --> "void" | "num" | "bool"
Identifier --> Letter (Letter | "_" | Digit)*

NumLiteral --> ("-")? (Digit)* (".")? (Digit)*
BooleanLiteral --> "true" | "false"

AddSub --> "+" | "-"
MulDiv --> "*" | "/"
Cond --> "&&" | "||"
Comp --> "<" | "<=" | "==" | ">=" | ">"
Letter --> ["A" - "Z", "a" - "z"]
Digit --> ["0" - "9"]
```
