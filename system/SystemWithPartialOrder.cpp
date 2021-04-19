//
// Created by ramizouari on 18/04/2021.
//

#include "SystemWithPartialOrder.h"

void SystemWithPartialOrder::set_default_name(std::string name)
{
    default_order_name=name;
}

SystemWithPartialOrder::SystemWithPartialOrder(IdentifiedVariableFactory<std::string> &_F,
                                               std::string order_name):
                                               SystemWithEquality(_F),
                                               less_equal(order_name)
{
    auto X=_F.new_instance("X");
    auto Y=_F.new_instance("Y");
    auto Z=_F.new_instance("Z");
    add_clause(less_equal(X,X));
    add_clause(~less_equal(X,Y)|~less_equal(Y,X)|equal(X,Y));
    add_clause(~equal(X,Y)|less_equal(X,Y));
    add_clause(~less_equal(X,Y) |~less_equal(Y,Z)|less_equal(X,Z));
    rename_all();
}

SymbolicPredicate_2 &SystemWithPartialOrder::get_order_symbol() {
    return less_equal;
}
