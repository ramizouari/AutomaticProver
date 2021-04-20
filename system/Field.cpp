//
// Created by ramizouari on 20/04/2021.
//

#include "Field.h"

Field::Field(IdentifiedVariableFactory<std::string> &F) : IntegralRing(F),mult_inverse("mult_inverse")
{
    auto __0=&neutral_element;
    auto __1=&_1;
    auto X=F.new_instance("X"),Y=F.new_instance("Y");
    add_clause(equal(X,__0)|equal(product(X,mult_inverse(X)),__1));
    rename_all();
}
