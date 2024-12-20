#include <gtest/gtest.h>
#include "calculator.h"

// Test 1: Berechnung des Umfangs eines Kreises
TEST(CalculatorTest, CalculateCircleCircumference) {
    Calculator calc;
    calc.define("pi", 3.1415);
    calc.define("r", 4);
    std::string expression = "2*pi*r";
    double result = calc.computeValue(expression);
    EXPECT_NEAR(result, 25.132, 0.001);
}

// Test 2: Berechnung eines komplexen Ausdrucks
TEST(CalculatorTest, CalculateComplexExpression1) {
    Calculator calc;
    calc.define("a", 2);
    calc.define("b", 3);
    calc.define("bb", 5);
    calc.define("ab", 7);
    std::string expression = "a + bb*b + ab";
    double result = calc.computeValue(expression);
    EXPECT_EQ(result, 24);
}

// Test 3: Berechnung eines anderen komplexen Ausdrucks
TEST(CalculatorTest, CalculateComplexExpression2) {
    Calculator calc;
    calc.define("a", 2);
    calc.define("b", 3);
    calc.define("bb", 5);
    calc.define("ab", 7);
    std::string expression = "(a + bb) * (b + ab)";
    double result = calc.computeValue(expression);
    EXPECT_EQ(result, 70);
}

// Division durch Null testen
TEST(CalculatorTest, DivisionByZero) {
    Calculator calc;
    EXPECT_THROW(calc.computeValue("1 / 0"), std::invalid_argument);
//    EXPECT_THROW(calc.computeValue("10 / (2 - 2)"), std::invalid_argument);
}

// Ungültige Zeichen
TEST(CalculatorTest, InvalidCharacter) {
    Calculator calc;
    EXPECT_THROW(calc.computeValue("5 + &"), std::invalid_argument);
//    EXPECT_THROW(calc.computeValue("5 + 3 *"), std::invalid_argument);
}

// Negative Exponenten
TEST(CalculatorTest, NegativeExponent) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.computeValue("2 ^ -3"), 0.125);
    EXPECT_DOUBLE_EQ(calc.computeValue("(-2) ^ 3"), -8);
}

// Variable ersetzen
TEST(CalculatorTest, VariableReplacement) {
    Calculator calc;
    calc.define("x", 5);
    calc.define("y", 3);
    EXPECT_DOUBLE_EQ(calc.computeValue("x + y"), 8);
    EXPECT_DOUBLE_EQ(calc.computeValue("x * y + 2"), 17);
}

// Randfälle
TEST(CalculatorTest, EdgeCases) {
    Calculator calc;
    EXPECT_THROW(calc.computeValue(""), std::invalid_argument);
    EXPECT_THROW(calc.computeValue("5 + (3 * 2"), std::invalid_argument);
    EXPECT_THROW(calc.computeValue("5 + 3 * ) 2"), std::invalid_argument);
}

// Undefinierte Variablen
TEST(CalculatorTest, UndefinedVariable) {
    Calculator calc;
    EXPECT_THROW(calc.computeValue("x + 5"), std::invalid_argument);
}

// Mehrfach-Operatoren testen
TEST(CalculatorTest, MultipleOperators) {
    Calculator calc;
    EXPECT_THROW(calc.computeValue("5 ** 2"), std::invalid_argument);
}

// Große Zahlen testen
TEST(CalculatorTest, LargeNumbers) {
    Calculator calc;
    calc.define("big", 1e10);
    EXPECT_DOUBLE_EQ(calc.computeValue("big + 1"), 1e10 + 1);
}

// Verschachtelte Klammern
TEST(CalculatorTest, NestedParentheses) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.computeValue("((2 + 3) * 4) - 5"), 15);
    EXPECT_DOUBLE_EQ(calc.computeValue("((2 + (3 * 4)) - 5) / 3"), 3);
}



// Komplexe Ausdrücke
TEST(CalculatorTest, ComplexExpressions) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.computeValue("3 + 5 * 2"), 13);
    EXPECT_DOUBLE_EQ(calc.computeValue("(1 + 2) * (3 + 4)"), 21);
    EXPECT_DOUBLE_EQ(calc.computeValue("10 - 2 ^ 3 + 4 / 2"), 4);
}
