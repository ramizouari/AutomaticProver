//
// Created by ramizouari on 15/04/2021.
//

#ifndef AUTOMATICPROVER_IDENTIFIEDSYMBOL_H
#define AUTOMATICPROVER_IDENTIFIEDSYMBOL_H
#include "Variable.h"
#include "SymbolicPredicate.h"
#include "SymbolicFunction.h"

template<class S,typename I>
class IdentifiedSymbol :public S
{
    I name;
public:
    template<typename ...A>
    IdentifiedSymbol(I _name,A... s):S(s...),name(_name){}
};

template<typename I>
using IdentifiedSymbolicFunction = IdentifiedSymbol<SymbolicFunction,I>;


template<typename I>
using IdentifiedSymbolicConstant = IdentifiedSymbol<SymbolicConstant,I>;

template<typename I>
using IdentifiedVariable = IdentifiedSymbol<Variable,I>;

template<typename I>
using IdentifiedSymbolicPredicate = IdentifiedSymbol<SymbolicPredicate,I>;


#endif //AUTOMATICPROVER_IDENTIFIEDSYMBOL_H
