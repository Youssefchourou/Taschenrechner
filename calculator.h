#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <unordered_map>
#include <stack>
#include <cmath>

class Calculator {
public:
    Calculator();
    ~Calculator();

    void define(const std::string& name, double value);
    double computeValue(const std::string& expression);

private:
    std::unordered_map<std::string, double> variables_;

    std::string replaceVariables(const std::string& expression);
    double evaluateExpression(const std::string& expression);

    bool isOperator(char c);
    int precedence(char op);
    void computeTop(std::stack<char>& ops, std::stack<double>& values);

    // Unterstützung für trigonometrische Funktionen
};

#endif // CALCULATOR_H
