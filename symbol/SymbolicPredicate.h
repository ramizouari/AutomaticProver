//
// Created by ramizouari on 14/04/2021.
//

#ifndef AUTOMATICPROVER_SYMBOLICPREDICATE_H
#define AUTOMATICPROVER_SYMBOLICPREDICATE_H
#include "Symbol.h"

class SymbolicPredicate :public Symbol{
    const int n;
public:
    SymbolicPredicate(int _n);
    int arg_count() override;
    bool is_variable() override;
};

template<int p>
class SymbolicPredicate_p: public SymbolicPredicate
{
public:
    SymbolicPredicate_p(): SymbolicPredicate(p){}
};
using SymbolicProposition=SymbolicPredicate_p<0>;

#endif //AUTOMATICPROVER_SYMBOLICPREDICATE_H
