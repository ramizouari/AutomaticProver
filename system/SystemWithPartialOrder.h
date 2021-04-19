//
// Created by ramizouari on 18/04/2021.
//

#ifndef AUTOMATICPROVER_SYSTEMWITHPARTIALORDER_H
#define AUTOMATICPROVER_SYSTEMWITHPARTIALORDER_H
#include <string>
#include "symbol/IdentifiedSymbol.h"
#include "factory/IdentifiedVariableFactory.h"
#include "System.h"
#include "SystemWithEquality.h"

class SystemWithPartialOrder :public SystemWithEquality{
protected:
    IdentifiedSymbolicPredicate_2<std::string> less_equal;
    inline static std::string default_order_name="leq";
public:
    static void set_default_name(std::string name);
    SystemWithPartialOrder(IdentifiedVariableFactory<std::string> &_F,std::string order_name);
    SymbolicPredicate_2& get_order_symbol();
};


#endif //AUTOMATICPROVER_SYSTEMWITHPARTIALORDER_H
