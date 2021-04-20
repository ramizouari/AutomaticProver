//
// Created by ramizouari on 20/04/2021.
//

#include "CommutativeRing.h"

CommutativeRing::CommutativeRing(IdentifiedVariableFactory<std::string> &F) : Ring(F)
{
    auto __0=&neutral_element;
    auto __1=&_1;
    auto X=F.new_instance("X"),Y=F.new_instance("Y");
    add_clause(equal(product(X,Y),product(Y,X)));
    rename_all();
}
