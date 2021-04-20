//
// Created by ramizouari on 18/04/2021.
//

#include "SystemWithEquality.h"

SystemWithEquality::SystemWithEquality(IdentifiedVariableFactory<std::string> &_F): PredicateSystem(_F), equal("equal")
{
    auto X=_F.new_instance("X"),Y=_F.new_instance("Y"),Z=_F.new_instance("Z");
    add_clause(equal(X,X));
    add_clause(~equal(X,Y)|equal(Y,X));
    add_clause(~equal(X,Y)|~equal(Y,Z)|equal(X,Z));
    rename_all();
}

SymbolicPredicate_2 &SystemWithEquality::get_equality_symbol() {
    return equal;
}
