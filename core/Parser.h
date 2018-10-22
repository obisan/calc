//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_PARSER_H
#define AST_TEST_PARSER_H

#include "ASTNode.h"
#include "Token.h"
#include "../exception/ParserException.h"

class Parser {
    Token           m_crtToken;
    const char*     m_Text;
    size_t          m_Index;

private:

    ASTNode* Expression() {
        ASTNode* tnode = Term();
        ASTNode* e1node = Expression1();

        return CreateNode(OperatorPlus, tnode, e1node);
    }

    ASTNode* Expression1() {
        ASTNode* tnode;
        ASTNode* e1node;

        switch(m_crtToken.Type) {
            case Plus:
                GetNextToken();
                tnode = Term();
                e1node = Expression1();

                return CreateNode(OperatorPlus, e1node, tnode);

            case Minus:
                GetNextToken();
                tnode = Term();
                e1node = Expression1();

                return CreateNode(OperatorMinus, e1node, tnode);

            default:
                break;
        }

        return CreateNodeNumber(0);
    }

    ASTNode* Term() {
        ASTNode* fnode = Factor();
        ASTNode* t1node = Term1();

        return CreateNode(OperatorMul, fnode, t1node);
    }

    ASTNode* Term1() {
        ASTNode* fnode;
        ASTNode* t1node;

        switch(m_crtToken.Type)
        {
            case Mul:
                GetNextToken();
                fnode = Factor();
                t1node = Term1();
                return CreateNode(OperatorMul, t1node, fnode);

            case Div:
                GetNextToken();
                fnode = Factor();
                t1node = Term1();
                return CreateNode(OperatorDiv, t1node, fnode);

            default:
                break;
        }

        return CreateNodeNumber(1);
    }

    ASTNode* Factor() {
        ASTNode* node;
        switch(m_crtToken.Type)
        {
            case OpenParenthesis:
                GetNextToken();
                node = Expression();
                Match(')');
                return node;

            case Minus:
                GetNextToken();
                node = Factor();
                return CreateUnaryNode(node);

            case Number:
            {
                double value = m_crtToken.Value;
                GetNextToken();
                return CreateNodeNumber(value);
            }

            default:
            {
                std::stringstream sstr;
                sstr << "Unexpected token '" << m_crtToken.Symbol << "' at position " << m_Index;
                throw ParserException(sstr.str(), m_Index);
            }
        }
    }

    ASTNode* CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right) {
        ASTNode* node = new ASTNode;
        node->Type = type;
        node->Left = left;
        node->Right = right;

        return node;
    }

    ASTNode* CreateUnaryNode(ASTNode* left) {
        ASTNode* node = new ASTNode;
        node->Type = UnaryMinus;
        node->Left = left;
        node->Right = nullptr;

        return node;
    }

    ASTNode* CreateNodeNumber(double value) {
        ASTNode* node = new ASTNode;
        node->Type = NumberValue;
        node->Value = value;

        return node;
    }

    void Match(char expected) {
        if(m_Text[m_Index - 1] == expected)
            GetNextToken();
        else
        {
            std::stringstream sstr;
            sstr << "Expected token '" << expected << "' at position " << m_Index;
            throw ParserException(sstr.str(), m_Index);
        }
    }

    void SkipWhitespaces() {
        while(isspace(m_Text[m_Index])) m_Index++;
    }

    void GetNextToken() {
        SkipWhitespaces();

        m_crtToken.Value = 0;
        m_crtToken.Symbol = 0;

        if(m_Text[m_Index] == 0) {
            m_crtToken.Type = EndOfText;
            return;
        }

        if(isdigit(m_Text[m_Index])) {
            m_crtToken.Type = Number;
            m_crtToken.Value = GetNumber();
            return;
        }

        m_crtToken.Type = Error;

        switch(m_Text[m_Index]) {
            case '+': m_crtToken.Type = Plus;               break;
            case '-': m_crtToken.Type = Minus;              break;
            case '*': m_crtToken.Type = Mul;                break;
            case '/': m_crtToken.Type = Div;                break;
            case '(': m_crtToken.Type = OpenParenthesis;    break;
            case ')': m_crtToken.Type = ClosedParenthesis;  break;
            default:                                        break;
        }

        if(m_crtToken.Type != Error) {
            m_crtToken.Symbol = m_Text[m_Index];
            m_Index++;
        }
        else {
            std::stringstream sstr;
            sstr << "Unexpected token '" << m_Text[m_Index] << "' at position " << m_Index;
            throw ParserException(sstr.str(), m_Index);
        }
    }

    double GetNumber() {
        SkipWhitespaces();

        size_t index = m_Index;
        while(isdigit(m_Text[m_Index])) m_Index++;
        if(m_Text[m_Index] == '.') m_Index++;
        while(isdigit(m_Text[m_Index])) m_Index++;

        if(m_Index - index == 0)
            throw ParserException("Number expected but not found!", m_Index);

        char buffer[32] = {0};
        memcpy(buffer, &m_Text[index], m_Index - index);

        return atof(buffer);
    }

public:
    ASTNode* Parse(const char* text) {
        m_Text = text;
        m_Index = 0;
        GetNextToken();

        return Expression();
    }
};


#endif //AST_TEST_PARSER_H
