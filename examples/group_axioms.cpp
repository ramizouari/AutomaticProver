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
    SymbolicFunction_2 &product = *new IdentifiedSymbolicFunction_2<std::string>("product");
    SymbolicFunction_1  &inverse=*new IdentifiedSymbolicFunction_1<std::string>("inverse");
    SymbolicPredicate_2 &equal= *new IdentifiedSymbolicPredicate_2<std::string>("equal");
    SymbolicFunction_1 &f=*new IdentifiedSymbolicFunction_1<std::string>("f");
    Clause equality_symmetric({~equal(X,Y),equal(Y,X)});
    Clause equality_transitive({~equal(X,Y),~equal(Y,Z),equal(X,Z)});
    Clause equality_reflexive({equal(X,X)});
    Clause equality_existence({equal(X,f(X))});
    Clause associativity({
                         equal(product(product(X,Y),Z),product(X,product(Y,Z)))});
    Clause commutativity({equal(product(X,Y),product(Y,X))});
    Clause equality_preservation({~equal(X,Y),~equal(Z,U),
                                  equal(product(X,Z),product(Z,U))});
    Clause not_right_neutral({~equal(product(e,a),a)});
    Clause left_neutral({equal(product(X,e),X)});
    Clause right_inverse({equal(product(X,inverse(X)),e)});
    Clause left_inverse({equal(product(inverse(X),X),e)});
    Clause is_identity({equal(product(a,a),a)});
    Clause absurd({~equal(a,e)});
    Predicate consequence(~equal(product(product(a,a),product(b,b)),
                          product(product(a,b),product(a,b))));
    System S({equality_symmetric,equality_preservation,associativity,commutativity,
              left_inverse,right_inverse,is_identity,absurd},
             factory);
    for(auto T:S.get_theorems())
        std::cout << T.get_name() << '\n';
    std::cout << S.check_consistency();
}