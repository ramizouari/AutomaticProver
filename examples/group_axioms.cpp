//
// Created by ramizouari on 17/04/2021.
//

#include "symbol/SymbolicFunction.h"
#include "symbol/Variable.h"
#include "symbol/IdentifiedSymbol.h"
#include "factory/IdentifiedVariableFactory.h"
#include <string>
#include <iostream>
#include <system/PredicateSystem.h>
#include "system/algebraic/Group.h"
#include "system/algebraic/MedianAlgebra.h"
#include "prover/HerbrandProver.h"

int main()
{
    IdentifiedVariableFactory<std::string> factory;
    Variable *X = factory.new_instance("X"),*Y = factory.new_instance("Y"),
    *Z = factory.new_instance("Z"),*U=factory.new_instance("U"),
    *V=factory.new_instance("V"),*W=factory.new_instance("W"),
    *T=factory.new_instance("T"),*Q=factory.new_instance("Q");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    SymbolicConstant *b = new IdentifiedSymbolicConstant<std::string>("b");
    SymbolicConstant *c = new IdentifiedSymbolicConstant<std::string>("c");
    SymbolicConstant *d = new IdentifiedSymbolicConstant<std::string>("d");

    Group S(factory);
    S.set_limit(4e6);
    auto &equal=S.get_equality_symbol();
    auto &inverse=S.get_inverse();
    auto &product=S.get_product();
    auto e=S.get_neutral_element();
    S.add_goal(equal(product(a,b),product(a,c)));
    S.add_goal(~equal(b,c));
    Substitution sigma;
    Clause C1=equal(X,X);
    Clause C2=~equal(U,e)|~equal(a,U);
    //sigma.to_normal_form();
    sigma = pgu(equal(X,e),equal(U,U)).value();
    sigma(C1);
    sigma(C2);
    // S.add_goal(~equal(inverse(inverse(e)),e));

    S.rename_all();
    HerbrandProver H;
    for(auto T:S.get_theorems())
        std::cout << T.get_name() << '\n';
    std::cout << S.check_consistency();
}