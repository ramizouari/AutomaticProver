//
// Created by ramizouari on 18/04/2021.
//

#ifndef AUTOMATICPROVER_GROUP_H
#define AUTOMATICPROVER_GROUP_H
#include "SystemWithEquality.h"
#include "symbol/IdentifiedSymbol.h"

class Group: public SystemWithEquality
{
    IdentifiedSymbolicConstant<std::string> neutral_element;
    IdentifiedSymbolicFunction_1<std::string> inverse;
    IdentifiedSymbolicFunction_2<std::string> product;
public:
    Group(IdentifiedVariableFactory<std::string> &F);
    SymbolicConstant* get_neutral_element();
    SymbolicFunction_1& get_inverse();
    SymbolicFunction_2& get_product();
};


#endif //AUTOMATICPROVER_GROUP_H
