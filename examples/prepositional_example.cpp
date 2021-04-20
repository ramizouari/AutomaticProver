//
// Created by ramizouari on 20/04/2021.
//

#include "symbol/SymbolicFunction.h"
#include "symbol/Variable.h"
#include "symbol/IdentifiedSymbol.h"
#include "factory/IdentifiedVariableFactory.h"
#include <string>
#include <iostream>
#include "system/PrepositionalSystem.h"


int main()
{
    IdentifiedVariableFactory<std::string> factory;
    SymbolicConstant *e = new IdentifiedSymbolicConstant<std::string>("e");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    SymbolicConstant *b = new IdentifiedSymbolicConstant<std::string>("b");
    SymbolicConstant *c = new IdentifiedSymbolicConstant<std::string>("c");
    SymbolicFunction_1 &f=*new IdentifiedSymbolicFunction_1<std::string>("f");
    SymbolicPredicate_1 &happy=*new IdentifiedSymbolicPredicate_1<std::string>("happy");
    PrepositionalSystem S({happy(f(a))|happy(b),~happy(a),~happy(b)});

    for(auto T:S.get_theorems())
        std::cout << T.get_name() << '\n';
    std::cout << S.check_consistency();
}