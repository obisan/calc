//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_ENUMS_H
#define AST_TEST_ENUMS_H

enum ASTNodeType {
    Undefined,
    OperatorPlus,
    OperatorMinus,
    OperatorMul,
    OperatorDiv,
    UnaryMinus,
    NumberValue
};

enum TokenType {
    Error,
    Plus,
    Minus,
    Mul,
    Div,
    EndOfText,
    OpenParenthesis,
    ClosedParenthesis,
    Number
};

#endif //AST_TEST_ENUMS_H
