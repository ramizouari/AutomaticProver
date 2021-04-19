//
// Created by ramizouari on 18/04/2021.
//

//
// Created by ramizouari on 17/04/2021.
//

#include "symbol/SymbolicFunction.h"
#include "symbol/Variable.h"
#include "symbol/IdentifiedSymbol.h"
#include "factory/IdentifiedVariableFactory.h"
#include "system/SystemWithPartialOrder.h"
#include <string>
#include <iostream>
#include <system/System.h>


int main()
{
    IdentifiedVariableFactory<std::string> factory;
    SymbolicConstant *e = new IdentifiedSymbolicConstant<std::string>("e");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    SymbolicConstant *b = new IdentifiedSymbolicConstant<std::string>("b");
    SymbolicConstant *c = new IdentifiedSymbolicConstant<std::string>("c");
    SymbolicFunction_1 &f=*new IdentifiedSymbolicFunction_1<std::string>("f");
    SystemWithPartialOrder S(factory,"leq");
    auto& less_eq = S.get_order_symbol();
    auto& equal=S.get_equality_symbol();
    auto X=factory.new_instance("X"),Y=factory.new_instance("Y"),Z=factory.new_instance("Z");
    S.set_limit(4e6);
    S.add_clause(less_eq(f(X),e));
    S.add_clause(less_eq(e,f(e)));
    S.add_clause(~equal(e,f(e)));
    S.rename_all();
    for(auto T:S.get_theorems())
        std::cout << T.get_name() << '\n';
    std::cout << S.check_consistency();
}