//
// Created by ramizouari on 17/04/2021.
//

#ifndef AUTOMATICPROVER_IDENTIFIABLESYMBOL_H
#define AUTOMATICPROVER_IDENTIFIABLESYMBOL_H


template<typename I>
class IdentifiableSymbol : virtual public Identifiable<I>,virtual public Symbol
{
};

#endif //AUTOMATICPROVER_IDENTIFIABLESYMBOL_H
