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
#include <system/PredicateSystem.h>
#include "prover/HerbrandProver.h"
#include "prover/ResolutionProver.h"

int main()
{
    IdentifiedVariableFactory<std::string> factory;
    SymbolicConstant *e = new IdentifiedSymbolicConstant<std::string>("e");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    SymbolicConstant *b = new IdentifiedSymbolicConstant<std::string>("b");
    SymbolicConstant *c = new IdentifiedSymbolicConstant<std::string>("c");
    SymbolicConstant *d = new IdentifiedSymbolicConstant<std::string>("d");
    SymbolicConstant *h = new IdentifiedSymbolicConstant<std::string>("h");

    SymbolicFunction_1 &f=*new IdentifiedSymbolicFunction_1<std::string>("f");
    SymbolicFunction_1 &g=*new IdentifiedSymbolicFunction_1<std::string>("g");

    SystemWithPartialOrder S(factory,"leq");
    auto& less_eq = S.get_order_symbol();
    auto& equal=S.get_equality_symbol();
    auto X=factory.new_instance("X"),Y=factory.new_instance("Y"),Z=factory.new_instance("Z");
    S.set_limit(4e6);
    S.add_goal(less_eq(a,b));
    S.add_goal(less_eq(b,c));
    S.add_goal(less_eq(c,d));
    S.add_goal(less_eq(d,e));
    S.add_goal(less_eq(e,h));
    S.add_goal(less_eq(h,a));
    S.add_goal(~equal(a,b));
    ResolutionProver R_prover;
    R_prover.set_limit(3e6);
    S.rename_all();
    std::cout << S.check_consistency(R_prover) << '\n';
    for(auto T:R_prover.get_theorems())
        std::cout << T.get_name() << '\n';
}