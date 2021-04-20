//
// Created by ramizouari on 17/04/2021.
//

#ifndef AUTOMATICPROVER_IDENTIFIEDVARIABLEFACTORY_H
#define AUTOMATICPROVER_IDENTIFIEDVARIABLEFACTORY_H
#include "VariableFactory.h"
#include "symbol/IdentifiedSymbol.h"
#include <unordered_set>

template<typename I>
class IdentifiedVariableFactory : public VariableFactory
{
    inline static std::unordered_map<I,int> identifier_map;
    inline static int indeterminate_counter = 0;
public:
    Variable* new_instance(I S)
    {
        if(identifier_map.contains(S))
            return S_map[identifier_map[S]];
        Variable *w=new IdentifiedVariable<I>(S);
        int n=S_map.size();
        identifier_map[S]=n;
        S_map[n]=w;
        id_map[w]=n;
        return w;
    }

    Variable* new_instance()
    {
        indeterminate_counter++;
        std::stringstream S;
        S << "C" << indeterminate_counter;
        return new_instance(S.str());
    }
};
#endif //AUTOMATICPROVER_IDENTIFIEDVARIABLEFACTORY_H
