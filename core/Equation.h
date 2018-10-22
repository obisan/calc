//
// Created by Aleksandr Dubinets on 23/10/2018.
//

#ifndef AST_TEST_EQUATION_H
#define AST_TEST_EQUATION_H

#include "../stdafx.h"
#include "../exception/EquationException.h"

class Equation {
private:

    struct Variable {
        std::string key;
        std::string value;
    };

    std::string getValue(const std::string& variable) {
        std::string value;
        std::cout << variable << " = ";
        std::getline(std::cin, value);
        std::cout << "OK" << std::endl;
        return value;
    }

public:
    std::string Parse(const std::string& line) {

        if(line.empty())
            throw EquationException("Empty string!");


        std::string result(line);
        std::vector<Variable> variables;
        std::regex regex1("\\b[a-zA-Z]+[0-9]*");
        std::sregex_iterator it(line.begin(), line.end(), regex1);
        std::sregex_iterator it_end;

        while (it != it_end) {
            Variable variable;
            variable.key    = it->str();
            variable.value  = getValue(it->str());

            variables.push_back(variable);
            it++;
        }

        for (auto &variable : variables) {
            result.replace(
                    result.find(variable.key),
                    variable.key.size(),
                    variable.value
            );
        }

        return result;

    }
};


#endif //AST_TEST_EQUATION_H
