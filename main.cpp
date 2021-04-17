#include <iostream>
#include "system/System.h"
#include "factory/VariableFactory.h"
#include "symbol/IdentifiedSymbol.h"

/*
 * Example:
 * All humans are mortals;
 * Socrate is human
 * is Socrate Mortal?
 * */

int main() {
    VariableFactory factory;
    auto X=factory.new_instance();
    SymbolicFunction *f = new IdentifiedSymbolicFunction<std::string>("f",1);
    Symbol *h = new IdentifiedSymbolicFunction<std::string>("h",2);
    Symbol *s = new IdentifiedSymbolicFunction<std::string>("s",1);
    Symbol *a = new IdentifiedSymbolicConstant<std::string>("a");
    Literal w1(f,{X}),w2(s,{w1});
    Literal w(h, {w1,w2});
    std::cout << w.get_name();
    return 0;
}
