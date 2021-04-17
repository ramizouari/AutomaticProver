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
    *V=factory.new_instance("V");
    SymbolicConstant *e = new IdentifiedSymbolicConstant<std::string>("e");
    SymbolicConstant *a = new IdentifiedSymbolicConstant<std::string>("a");
    SymbolicConstant *b = new IdentifiedSymbolicConstant<std::string>("b");
    SymbolicFunction_1 *f = new IdentifiedSymbolicFunction_1<std::string>("f");
    SymbolicPredicate_2 *equal= new IdentifiedSymbolicPredicate_2<std::string>("equal");
    Clause equality_symmetric({~Predicate(equal,X,Y),Predicate(equal,Y,X)});
    Clause equality_transitive({~Predicate(equal,X,Y),~Predicate(equal,Y,Z),Predicate(equal,X,Z)});
    Clause equality_reflexive({~Predicate(equal,X,X)});
    Literal f_x(f,X);
    Literal f_a(f,a);
    Literal f4_a(f,Literal(f,Literal(f,Literal(f,X))));
    Clause equality_existence({Predicate(equal,X,f_x)});
    System S({equality_transitive,equality_symmetric,equality_existence,equality_reflexive},
             factory);
    for(auto T:S.get_theorems())
        std::cout << T.get_name() << '\n';
    std::cout << S.check_consistency();
}