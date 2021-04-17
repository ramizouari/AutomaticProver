#include <iostream>
#include "system/System.h"
#include "factory/VariableFactory.h"
#include "factory/IdentifiedVariableFactory.h"
#include "symbol/IdentifiedSymbol.h"

/*
 * Example:
 * All humans are mortals;
 * Socrate is human
 * is Socrate Mortal?
 * */

int main() {
    IdentifiedVariableFactory<std::string> factory;
    auto X=factory.new_instance("X");
    SymbolicFunction_1 *f = new IdentifiedSymbolicFunction_1<std::string>("f");
    SymbolicFunction_2 *h = new IdentifiedSymbolicFunction_2<std::string>("h");
    SymbolicFunction_1 *s = new IdentifiedSymbolicFunction_1<std::string>("s");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    Literal w1(f,X),w2(s,w1);
    Literal w(h, X,w2);
    std::cout << w.get_name();
    return 0;
}
