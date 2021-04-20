//
// Created by ramizouari on 20/04/2021.
//

#include "CommutativeGroup.h"

CommutativeGroup::CommutativeGroup(IdentifiedVariableFactory<std::string> &_F) : Group(_F) {
    auto X=_F.new_instance("X");
    auto Y=_F.new_instance("Y");
    add_clause(equal(group_op(X, Y), group_op(Y, X)));
    rename_all();
}

CommutativeGroup::CommutativeGroup(IdentifiedVariableFactory<std::string> &_F, std::string op_name, std::string e_name)
        : Group(_F, op_name, e_name)
{
    auto X=_F.new_instance("X");
    auto Y=_F.new_instance("Y");
    add_clause(equal(group_op(X, Y), group_op(Y, X)));
    rename_all();
}
