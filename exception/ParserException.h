//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_PARSEREXCEPTION_H
#define AST_TEST_PARSEREXCEPTION_H

#include "../stdafx.h"

class ParserException : public std::exception {
    int m_Pos;
    std::string message;

public:
    ParserException(std::string message, int pos):
            message(std::move(message)),
            m_Pos(pos)
    {}

    const char* what() const noexcept {
        return message.c_str();
    }

};

#endif //AST_TEST_PARSEREXCEPTION_H
