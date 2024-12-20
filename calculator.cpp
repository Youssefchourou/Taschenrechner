#include "calculator.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <stack>
#include <unordered_map>
#include <stdexcept>

Calculator::Calculator() {}

Calculator::~Calculator() {}

void Calculator::define(const std::string& name, double value) {
    variables_[name] = value;
}

double Calculator::computeValue(const std::string& expression) {
    if (expression.empty()) {
        throw std::invalid_argument("Error: Empty expression.");
    }

    try {
        std::string expr = replaceVariables(expression);
        return evaluateExpression(expr);
    } catch (const std::exception& e) {
        std::cerr << "Error in computeValue: " << e.what() << std::endl;
        throw;  // Weiterwerfen der Ausnahme zur korrekten Fehlerbehandlung
    }
}

std::string Calculator::replaceVariables(const std::string& expression) {
    std::string expr = expression;
    for (const auto& var : variables_) {
        size_t pos = expr.find(var.first);
        while (pos != std::string::npos) {
            expr.replace(pos, var.first.length(), std::to_string(var.second));
            pos = expr.find(var.first, pos + std::to_string(var.second).length());
        }
    }
    return expr;
}

double Calculator::evaluateExpression(const std::string& expression) {
    std::stack<double> values;
    std::stack<char> ops;

    for (size_t i = 0; i < expression.length(); i++) {
        if (isspace(expression[i])) continue;

        // Zahl oder Dezimalzahl erkennen
        if (isdigit(expression[i]) || expression[i] == '.' ||
            (expression[i] == '-' && (i == 0 || !isdigit(expression[i - 1])))) {
            size_t startPos = i;
            while (i < expression.length() &&
                   (isdigit(expression[i]) || expression[i] == '.' || expression[i] == 'e' ||
                    expression[i] == '+' || expression[i] == '-')) {
                i++;
            }
            try {
                double number = std::stod(expression.substr(startPos, i - startPos));
                values.push(number);
            } catch (...) {
                throw std::invalid_argument("Error: Invalid number format.");
            }
            i--;
        }
        // Klammern verarbeiten
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                computeTop(ops, values);
            }
            ops.pop();
        }
        // Operatoren verarbeiten
        else if (isOperator(expression[i])) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                computeTop(ops, values);
            }
            ops.push(expression[i]);
        }

        // Ungültige Zeichen
        else {
            throw std::invalid_argument(std::string("Invalid character in expression: ") + expression[i]);
        }
    }

    while (!ops.empty()) {
        computeTop(ops, values);
    }

    if (values.size() != 1) {
        throw std::invalid_argument("Error: Invalid expression.");
    }

    return values.top();
}

void Calculator::computeTop(std::stack<char>& ops, std::stack<double>& values) {
    if (values.size() < 2) {
        throw std::invalid_argument("Error: Insufficient operands.");
    }

    char op = ops.top();
    ops.pop();
    double right = values.top();
    values.pop();
    double left = values.top();
    values.pop();

    switch (op) {
    case '+': values.push(left + right); break;
    case '-': values.push(left - right); break;
    case '*': values.push(left * right); break;
    case '/':
        if (right == 0) throw std::invalid_argument("Error: Division by zero.");
        values.push(left / right);
        break;
    case '^': values.push(pow(left, right)); break;
    default: throw std::invalid_argument("Error: Unknown operator.");
    }
}

bool Calculator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int Calculator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}


