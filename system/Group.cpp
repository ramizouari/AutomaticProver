//
// Created by ramizouari on 18/04/2021.
//

#include "Group.h"

Group::Group(IdentifiedVariableFactory<std::string> &F) : SystemWithEquality(F), neutral_element("e"), group_op("product"),
                                                          inverse("inverse")
{
    auto X=F.new_instance("X"),Y=F.new_instance("Y"),Z=F.new_instance("Z");
    auto U=F.new_instance("U"),V=F.new_instance("V"),W=F.new_instance("W");
    auto e=&neutral_element;
    add_clause(equal(group_op(X, e), X));
    add_clause(equal(group_op(e, X), X));
    add_clause( ~equal(X,U)|~equal(Y,V)|equal(group_op(X, Y), group_op(U, V)));
    add_clause(equal(group_op(X, group_op(Y, Z)), group_op(group_op(X, Y), Z)));
    add_clause(equal(group_op(X, inverse(X)), e));
    add_clause(equal(group_op(inverse(X), X), e));
    rename_all();
}

SymbolicConstant *Group::get_neutral_element() {
    return &neutral_element;
}

SymbolicFunction_1 &Group::get_inverse() {
    return inverse;
}

SymbolicFunction_2 &Group::get_product() {
    return group_op;
}
