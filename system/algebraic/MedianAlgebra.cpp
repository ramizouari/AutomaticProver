//
// Created by ramizouari on 20/04/2021.
//

#include "MedianAlgebra.h"

SymbolicFunction_3 &MedianAlgebra::get_majority() {
    return majority;
}

MedianAlgebra::MedianAlgebra(IdentifiedVariableFactory<std::string> &_F) : SystemWithEquality(_F) , majority("majority")
{
    auto X=_F.new_instance("X"),Y=_F.new_instance("Y"),Z=_F.new_instance("Z"),
    U=_F.new_instance("U"),V=_F.new_instance("V"),W=_F.new_instance("W");
    add_clause(~equal(X,U)|~equal(Y,V)|~equal(Z,W)|equal(majority(X,Y,Z),majority(U,V,W)));
    add_clause(equal(majority(X,Y,Y),Y));
    add_clause(equal(majority(X,Y,Z),majority(Y,Z,X)));
    add_clause(equal(majority(majority(X,W,Y),W,Z),majority(X,W,majority(Y,W,Z))));
}
