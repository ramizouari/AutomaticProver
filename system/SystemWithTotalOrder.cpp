//
// Created by ramizouari on 18/04/2021.
//

#include "SystemWithTotalOrder.h"

SystemWithTotalOrder::SystemWithTotalOrder(IdentifiedVariableFactory<std::string> &_F, std::string order_name)
        : SystemWithPartialOrder(_F, order_name)
{
    auto X=_F.new_instance("X"),Y=_F.new_instance("Y");
    add_clause(less_equal(X,Y)|less_equal(Y,X));
    rename_all();
}
