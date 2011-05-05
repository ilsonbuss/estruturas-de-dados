/* 
 * File:   LL_main.cpp
 * Author: ilson.buss
 *
 * Created on 22 de Março de 2011, 10:06
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "validarExp.h"

using namespace std;



void testaExp(string s) {
	cout << "validarExp: '" << s << "' retornou ";
	cout << (validarExpressao(s.c_str()) ? "true" : "false") << endl;

}

void testaExps() {
	testaExp("([a + b])");
	testaExp("([[a + b])");
	testaExp("(");
	testaExp("(a))");
	testaExp("{a + [  ( x - y ) - z ] & true }");
	testaExp("{a + (  [ x - y ) - z ] & true }");
	testaExp("(a + (  ( x - y ) - z ) & true )");
	testaExp("(");
	testaExp("((({{{[]}}})))");
	testaExp("}");
	testaExp("[{}{}{}{}]");
	testaExp("((((()))])");
}



