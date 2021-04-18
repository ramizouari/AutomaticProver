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
#include <string>
#include <iostream>
#include <system/System.h>


int main()
{
    IdentifiedVariableFactory<std::string> factory;
    Variable *X = factory.new_instance("X"),*Y = factory.new_instance("Y"),
            *Z = factory.new_instance("Z"),*U=factory.new_instance("U"),
            *V=factory.new_instance("V"),*W=factory.new_instance("W"),
            *T=factory.new_instance("T"),*Q=factory.new_instance("Q");
    SymbolicConstant *e = new IdentifiedSymbolicConstant<std::string>("e");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    SymbolicConstant *b = new IdentifiedSymbolicConstant<std::string>("b");
    SymbolicFunction_1 &f=* new IdentifiedSymbolicFunction_1<std::string>("f");
    SymbolicPredicate_2 &leq= *new IdentifiedSymbolicPredicate_2<std::string>("leq");
    Clause reflexive(leq(X,X));
    Clause transitive(~leq(X,Y)|~leq(Y,Z)|leq(X,Z));
    Clause total(leq(X,Y)|leq(Y,X));
    Clause ascending_chain(leq(X,f(X)));
    Clause absurd_supposition(~leq(a,f(f(f(f(f(f(a))))))));
    System S({reflexive,transitive,total,ascending_chain,absurd_supposition},
             factory);
    for(auto T:S.get_theorems())
        std::cout << T.get_name() << '\n';
    std::cout << S.check_consistency();
}