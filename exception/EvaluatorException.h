//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_EVALUATOREXCEPTION_H
#define AST_TEST_EVALUATOREXCEPTION_H

#include "../stdafx.h"

class EvaluatorException : public std::exception {
    std::string message;
public:
    EvaluatorException(std::string message):
            message(std::move(message))
    {}

    const char* what() const noexcept {
        return message.c_str();
    }
};

#endif //AST_TEST_EVALUATOREXCEPTION_H
