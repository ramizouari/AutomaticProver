//
// Created by ramizouari on 14/04/2021.
//

#ifndef AUTOMATICPROVER_SYMBOLICPREDICATE_H
#define AUTOMATICPROVER_SYMBOLICPREDICATE_H
#include "Symbol.h"

class SymbolicPredicate :virtual public Symbol{
    const int n;
public:
    SymbolicPredicate(int _n);
    virtual int arg_count() override;
    virtual bool is_variable() override;
};

template<int p>
class SymbolicPredicate_p: public SymbolicPredicate
{
public:
    SymbolicPredicate_p(): SymbolicPredicate(p){}
};
using SymbolicPreposition=SymbolicPredicate_p<0>;
using SymbolicPredicate_1=SymbolicPredicate_p<1>;
using SymbolicPredicate_2=SymbolicPredicate_p<2>;
using SymbolicPredicate_3=SymbolicPredicate_p<3>;

#endif //AUTOMATICPROVER_SYMBOLICPREDICATE_H
