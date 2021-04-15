//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_SYMBOLICFUNCTION_H
#define AUTOMATICPROVER_SYMBOLICFUNCTION_H
#include "Symbol.h"

class SymbolicFunction : public Symbol
{
    const int n;
public:
    SymbolicFunction(int _n);
    int arg_count() override;
    bool is_variable() override;
};

template<int p>
class SymbolicFunction_p: public SymbolicFunction
{
public:
    SymbolicFunction_p(): SymbolicFunction(p){}
};
using SymbolicConstant=SymbolicFunction_p<0>;

#endif //AUTOMATICPROVER_SYMBOLICFUNCTION_H
