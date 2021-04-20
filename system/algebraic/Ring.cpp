//
// Created by ramizouari on 20/04/2021.
//

#include "Ring.h"

Ring::Ring(IdentifiedVariableFactory<std::string> &F) : CommutativeGroup(F,"sum","0"),
_1("1"),product("product")
{
    auto X=F.new_instance("X"),Y=F.new_instance("Y"),Z=F.new_instance("Z"),
        U=F.new_instance("U"),V=F.new_instance("V");
    auto __1=&_1;
    auto &sum=group_op;
    add_clause(~equal(X,U)|~equal(Y,V)|equal(product(X,Y),product(U,V)));
    add_clause(equal(product(product(X,Y),Z),product(X,product(Y,Z))));
    add_clause(equal(product(X,__1),X));
    add_clause(equal(product(__1,X),X));
    add_clause(equal(product(sum(X,Y),Z),sum(product(X,Z),product(Y,Z))));
    add_clause(equal(product(X,sum(Y,Z)),sum(product(X,Y),product(X,Z))));
    rename_all();
}
