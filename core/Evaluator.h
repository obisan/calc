//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_EVALUATOR_H
#define AST_TEST_EVALUATOR_H

#include "../exception/EvaluatorException.h"
#include "ASTNode.h"
#include "../util/enums.h"

class Evaluator {
    double EvaluateSubtree(ASTNode* ast) {
        if(ast == nullptr)
            throw EvaluatorException("Incorrect syntax tree!");

        if(ast->Type == NumberValue)
            return ast->Value;
        else if(ast->Type == UnaryMinus)
            return -EvaluateSubtree(ast->Left);
        else {
            double v1 = EvaluateSubtree(ast->Left);
            double v2 = EvaluateSubtree(ast->Right);
            switch(ast->Type) {
                case OperatorPlus:  return v1 + v2;
                case OperatorMinus: return v1 - v2;
                case OperatorMul:   return v1 * v2;
                case OperatorDiv:   return v1 / v2;
                default: break;
            }
        }

        throw EvaluatorException("Incorrect syntax tree!");
    }

public:
    double Evaluate(ASTNode* ast) {
        if(ast == nullptr)
            throw EvaluatorException("Incorrect abstract syntax tree");

        return EvaluateSubtree(ast);
    }
};


#endif //AST_TEST_EVALUATOR_H
