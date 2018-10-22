cmake_minimum_required(VERSION 3.12)
project(ast_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(ast_test main.cpp core/ASTNode.h stdafx.h core/Parser.h core/Token.h util/enums.h exception/ParserException.h exception/EvaluatorException.h exception/EquationException.h core/Evaluator.h core/Equation.h)