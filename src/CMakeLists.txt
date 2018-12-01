PROJECT(InterpreterCore)

set(LIBRARY_OUTPUT_PATH ${INTERPRETER_LIB_OUT_PATH})

add_library(${PROJECT_NAME} input_source.cpp
                            evaluator.cpp
                            lexer.cpp
                            parser.cpp
                            token.cpp
                            utility.cpp
                            operator.cpp
                            typechecker.cpp
                            interpreter.cpp)