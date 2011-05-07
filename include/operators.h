/* 
 * File:   operators.h
 * Author: ACER
 *
 * Created on 6 de Maio de 2011, 18:44
 */

#ifndef OPERATORS_H
#define	OPERATORS_H

#include <string>
using namespace std;

/**
 * Operadores relativos
 */
enum RelationalOperator {
    INVALID_OPERATOR,
    EQUAL,
    LESS_OR_EQUAL,
    GREATER_OR_EQUAL,
    LESS,
    GREATER,
    NOT_EQUAL
};

//Obtém o caractere relacional
static inline string relational2string(RelationalOperator ro) {
    switch(ro) {
        case EQUAL: return "==";
        case LESS_OR_EQUAL: return "<=";
        case GREATER_OR_EQUAL: return ">=";
        case LESS: return "<";
        case GREATER: return ">";
        case NOT_EQUAL: return "!=";
        default: return "??";
    }
}

//Obtém o caractere relacional
static inline RelationalOperator string2relational(string str) {
    if(str == "==" || str == "=") return EQUAL;
    else if(str == "<=") return LESS_OR_EQUAL;
    else if(str == ">=") return GREATER_OR_EQUAL;
    else if(str == "<") return LESS;
    else if(str == ">") return GREATER;
    else if(str == "!=" || str == "<>" || str == "~=") return NOT_EQUAL;
    else return INVALID_OPERATOR;
}

//Obtém o caractere relacional
static inline bool relationalMatch(RelationalOperator ro, int dif) {
    switch(ro) {
        case EQUAL: return dif == 0;
        case LESS_OR_EQUAL: return dif <= 0;
        case GREATER_OR_EQUAL: return dif >= 0;
        case LESS: return dif < 0;
        case GREATER: return dif > 0;
        case NOT_EQUAL: return dif != 0;
        default: return false;
    }
}

#endif	/* OPERATORS_H */

