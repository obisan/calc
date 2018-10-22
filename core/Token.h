//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_TOKEN_H
#define AST_TEST_TOKEN_H

#include "../util/enums.h"

struct Token {
    TokenType   Type;
    double      Value;
    char      Symbol;

    Token():Type(Error), Value(0), Symbol(0)
    {}
};

#endif //AST_TEST_TOKEN_H
