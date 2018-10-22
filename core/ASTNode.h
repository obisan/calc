//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_ASTNODE_H
#define AST_TEST_ASTNODE_H

#include "../stdafx.h"
#include "../util/enums.h"

class ASTNode {
public:
    ASTNodeType Type;
    double      Value;
    ASTNode*    Left;
    ASTNode*    Right;

    ASTNode() {
        Type = Undefined;
        Value = 0;
        Left = nullptr;
        Right = nullptr;
    }

    ~ASTNode() {
        delete Left;
        delete Right;
    }
};

#endif //AST_TEST_ASTNODE_H
