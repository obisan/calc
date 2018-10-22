#include "stdafx.h"
#include "core/Parser.h"
#include "core/Equation.h"
#include "core/Evaluator.h"

void calc(const char *text);

int main() {

    std::cout << "use \'exit\' to end app" << std::endl;
    std::cout << "> ";

    for(std::string line; std::getline(std::cin, line);){
        if("exit" == line) {
            break;
        }

        calc(line.c_str());

    }

    calc("1+2 + 3+4");
    calc("1*2*3*4");
    calc("1-2-3-4");
    calc("1/2/3/4");
    calc("1*2+3*4");
    calc("1+2*3+4");
    calc("(1+2)*(3+4)");
    calc("1+(2*3)*(4+5)");
    calc("1+(2*3)/4+5");
    calc("5/(4+3)/2");
    calc("1 + 2.5");
    calc("125");
    calc("-1");
    calc("-1+(-2)");
    calc("-1+(-2.0)");

    calc("   1*2,5");
    calc("   1*2.5e2");
    calc("M1 + 2.5");
    calc("1 + 2&5");
    calc("1 * 2.5.6");
    calc("1 ** 2.5");
    calc("*1 / 2.5");

    return 0;
}

void calc(const char *text) {
    Parser parser;
    Equation equation;

    try {
        std::string eq = equation.Parse(text);

        try {
            std::unique_ptr<ASTNode> ast(parser.Parse(eq.c_str()));

            try {
                Evaluator eval;
                double val = eval.Evaluate(ast.get());

                std::cout << text << " = " << val << std::endl;
            }
            catch(EvaluatorException& ex) {
                std::cout << text << " t " << ex.what() << std::endl;
            }
        }
        catch(ParserException& ex) {
            std::cout << text << " t " << ex.what() << std::endl;
        }
    } catch (EquationException& ex) {
        std::cout << text << " t " << ex.what() << std::endl;
    }

}
