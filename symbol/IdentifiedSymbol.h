//
// Created by ramizouari on 15/04/2021.
//

#ifndef AUTOMATICPROVER_IDENTIFIEDSYMBOL_H
#define AUTOMATICPROVER_IDENTIFIEDSYMBOL_H
#include "Variable.h"
#include "SymbolicPredicate.h"
#include "SymbolicFunction.h"
#include "Identifiable.h"
#include "IdentifiableSymbol.h"


template<class S,typename I>
class IdentifiedSymbol : public S,virtual public IdentifiableSymbol<I>
{
    I name;
public:
    template<typename ...A>
    IdentifiedSymbol(I _name,A... s):S(s...),name(_name){}
    I get_name() override
    {
        return name;
    }
};



template<typename I>
using IdentifiedSymbolicFunction = IdentifiedSymbol<SymbolicFunction,I>;

template<int p,typename I>
using IdentifiedSymbolicFunction_p = IdentifiedSymbol<SymbolicFunction_p<p>,I>;
template<typename I>
using IdentifiedSymbolicFunction_1 = IdentifiedSymbol<SymbolicFunction_p<1>,I>;
template<typename I>
using IdentifiedSymbolicFunction_2 = IdentifiedSymbol<SymbolicFunction_p<2>,I>;
template<typename I>
using IdentifiedSymbolicFunction_3 = IdentifiedSymbol<SymbolicFunction_p<3>,I>;
template<typename I>
using IdentifiedSymbolicFunction_4 = IdentifiedSymbol<SymbolicFunction_p<4>,I>;
template<typename I>
using IdentifiedSymbolicFunction_5 = IdentifiedSymbol<SymbolicFunction_p<5>,I>;

template<typename I>
using IdentifiedSymbolicConstant = IdentifiedSymbol<SymbolicConstant,I>;

template<typename I>
using IdentifiedVariable = IdentifiedSymbol<Variable,I>;

template<typename I>
using IdentifiedSymbolicPredicate = IdentifiedSymbol<SymbolicPredicate,I>;
template<typename I>
using IdentifiedSymbolicPreposition = IdentifiedSymbol<SymbolicPreposition ,I>;
template<int p,typename I>
using IdentifiedSymbolicPredicate_p = IdentifiedSymbol<SymbolicPredicate_p<p>,I>;
template<typename I>
using IdentifiedSymbolicPredicate_1 = IdentifiedSymbol<SymbolicPredicate_p<1>,I>;
template<typename I>
using IdentifiedSymbolicPredicate_2 = IdentifiedSymbol<SymbolicPredicate_p<2>,I>;
template<typename I>
using IdentifiedSymbolicPredicate_3 = IdentifiedSymbol<SymbolicPredicate_p<3>,I>;
template<typename I>
using IdentifiedSymbolicPredicate_4 = IdentifiedSymbol<SymbolicPredicate_p<4>,I>;
template<typename I>
using IdentifiedSymbolicPredicate_5 = IdentifiedSymbol<SymbolicPredicate_p<5>,I>;
#endif //AUTOMATICPROVER_IDENTIFIEDSYMBOL_H
