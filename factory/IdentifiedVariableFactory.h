//
// Created by ramizouari on 17/04/2021.
//

#ifndef AUTOMATICPROVER_IDENTIFIEDVARIABLEFACTORY_H
#define AUTOMATICPROVER_IDENTIFIEDVARIABLEFACTORY_H
#include "VariableFactory.h"
#include "../symbol/IdentifiedSymbol.h"

template<typename I>
class IdentifiedVariableFactory : public VariableFactory
{
public:
    Variable* new_instance(I S)
    {
        Variable *w=new IdentifiedVariable<I>(S);
        int n=S_map.size();
        S_map[n]=w;
        id_map[w]=n;
        return w;
    }
};
#endif //AUTOMATICPROVER_IDENTIFIEDVARIABLEFACTORY_H
