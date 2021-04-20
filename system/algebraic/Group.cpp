//
// Created by ramizouari on 18/04/2021.
//

#include "Group.h"

Group::Group(IdentifiedVariableFactory<std::string> &F) :
        Group(F,"product","e")
{

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

Group::Group(IdentifiedVariableFactory<std::string> &F, std::string operator_name, std::string neutral_name) :
SystemWithEquality(F),group_op(operator_name),neutral_element(neutral_name),inverse("inverse")
{
    /*
     * Let M be a model of our system
     * 1. = is an equivalence relation on M
     * 2. product is a well-defined binary operator on M/= x M/=
     * 3. inverse is a well-defined function on M/=
     * 4. M/= is a group
     * */
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
