//
// Created by ramizouari on 20/04/2021.
//

#include "IntegralRing.h"

IntegralRing::IntegralRing(IdentifiedVariableFactory<std::string> &F) : CommutativeRing(F) {
    auto __0=&neutral_element;
    auto __1=&_1;
    auto X=F.new_instance("X"),Y=F.new_instance("Y");
    add_clause(~equal(__0,__1));
    add_clause(~equal(product(X,Y),__0)|equal(X,__0)|equal(Y,__0));
    rename_all();
}
