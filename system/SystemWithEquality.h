//
// Created by ramizouari on 18/04/2021.
//

#ifndef AUTOMATICPROVER_SYSTEMWITHEQUALITY_H
#define AUTOMATICPROVER_SYSTEMWITHEQUALITY_H
#include "PredicateSystem.h"
#include "symbol/IdentifiedSymbol.h"
#include "factory/IdentifiedVariableFactory.h"

class SystemWithEquality :public PredicateSystem
{
protected:
    IdentifiedSymbolicPredicate_2<std::string> equal;
public:
    SystemWithEquality(IdentifiedVariableFactory<std::string> &_F);
    SymbolicPredicate_2& get_equality_symbol();
};


#endif //AUTOMATICPROVER_SYSTEMWITHEQUALITY_H
