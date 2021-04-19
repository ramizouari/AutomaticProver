//
// Created by ramizouari on 18/04/2021.
//

#ifndef AUTOMATICPROVER_SYSTEMWITHEQUALITY_H
#define AUTOMATICPROVER_SYSTEMWITHEQUALITY_H
#include "System.h"
#include "symbol/IdentifiedSymbol.h"
#include "factory/IdentifiedVariableFactory.h"

class SystemWithEquality :public System
{
protected:
    IdentifiedSymbolicPredicate_2<std::string> equal;
public:
    SystemWithEquality(IdentifiedVariableFactory<std::string> &_F);
    SymbolicPredicate_2& get_equality_symbol();
};


#endif //AUTOMATICPROVER_SYSTEMWITHEQUALITY_H
