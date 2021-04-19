//
// Created by ramizouari on 18/04/2021.
//

#include "Group.h"

Group::Group(IdentifiedVariableFactory<std::string> &F) : SystemWithEquality(F), neutral_element("e"), product("product"),
                                                          inverse("inverse")
{
    auto X=F.new_instance("X"),Y=F.new_instance("Y"),Z=F.new_instance("Z");
    auto U=F.new_instance("U"),V=F.new_instance("V"),W=F.new_instance("W");
    auto e=&neutral_element;
    add_clause(equal(product(X,e),X));
    add_clause(equal(product(e,X),X));
    add_clause( ~equal(X,U)|~equal(Y,V)|equal(product(X,Y),product(U,V)));
    add_clause(equal(product(X,product(Y,Z)),product(product(X,Y),Z)));
    add_clause(equal(product(X,inverse(X)),e));
    add_clause(equal(product(inverse(X),X),e));
    rename_all();
}

SymbolicConstant *Group::get_neutral_element() {
    return &neutral_element;
}

SymbolicFunction_1 &Group::get_inverse() {
    return inverse;
}

SymbolicFunction_2 &Group::get_product() {
    return product;
}
