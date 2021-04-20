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
#include "system/Group.h"

int main()
{
    IdentifiedVariableFactory<std::string> factory;
    Variable *X = factory.new_instance("X"),*Y = factory.new_instance("Y"),
    *Z = factory.new_instance("Z"),*U=factory.new_instance("U"),
    *V=factory.new_instance("V"),*W=factory.new_instance("W"),
    *T=factory.new_instance("T"),*Q=factory.new_instance("Q");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    SymbolicConstant *b = new IdentifiedSymbolicConstant<std::string>("b");
    SymbolicConstant *e1 = new IdentifiedSymbolicConstant<std::string>("e1");
    SymbolicConstant *e2 = new IdentifiedSymbolicConstant<std::string>("e2");
    SymbolicFunction_2 &product = *new IdentifiedSymbolicFunction_2<std::string>("product");
    SymbolicFunction_1 &inverse1 = *new IdentifiedSymbolicFunction_1<std::string>("inverse1");
    SymbolicFunction_1 &inverse2 = *new IdentifiedSymbolicFunction_1<std::string>("inverse2");

    SystemWithEquality S(factory);
    auto &equal=S.get_equality_symbol();
    S.set_limit(2e6);
    S.add_clause(equal(product(X,e1),X));
    S.add_clause(equal(product(e1,X),X));
    S.add_clause(~equal(X,U)|~equal(Y,V)|equal(product(X,Y),product(U,V)));
    S.add_clause(equal(product(X,product(Y,Z)),product(product(X,Y),Z)));
    S.add_clause(equal(product(X,Y),product(Y,X)));
    //S.add_clause(~equal(product(X,Y),U)|~equal(product(Y,Z),V)|equal(product(U,Z),product(X,V)));
    S.add_clause(equal(product(X,inverse1(X)),e1));
    S.add_clause(equal(product(inverse1(X),X),e1));
    S.add_clause(~equal(X,Y)|equal(inverse1(X),inverse1(Y)));
    //S.add_clause(~equal(X,Y)|equal(inverse2(X),inverse2(Y)));

    S.add_clause(~equal(inverse1(inverse1(e1)),e1));
    S.rename_all();
    for(auto T:S.get_theorems())
        std::cout << T.get_name() << '\n';
    std::cout << S.check_consistency();
}