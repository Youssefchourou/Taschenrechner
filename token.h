//
// Created by Youssef on 17.11.2024.
//

#ifndef TOKEN_H
#define TOKEN_H
#include<iostream>
#include<string>
using namespace std;

class Token {
public:



    enum TokenType {
        Number, Operator
    };
    Token(string value,TokenType tokentype);
private:

    string value;
    TokenType tokentype;

public:
    [[nodiscard]] TokenType tokentype1() const {
        return tokentype;
    }

    void set_tokentype(TokenType tokentype) {
        this->tokentype = tokentype;
    }

    [[nodiscard]] string value1() const {
        return value;
    }

    void set_value(const string &value) {
        this->value = value;
    }
};



#endif //TOKEN_H
