//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_SYMBOLICFUNCTION_H
#define AUTOMATICPROVER_SYMBOLICFUNCTION_H
#include "Symbol.h"
#include <vector>

class SymbolicFunction : virtual public Symbol
{
    const int n;
public:
    SymbolicFunction(int _n);
    virtual int arg_count() override;
    virtual bool is_variable() override;

};

template<int p>
class SymbolicFunction_p: public SymbolicFunction
{
public:
    SymbolicFunction_p(): SymbolicFunction(p){}
};
using SymbolicConstant=SymbolicFunction_p<0>;
using SymbolicFunction_1=SymbolicFunction_p<1>;
using SymbolicFunction_2=SymbolicFunction_p<2>;
using SymbolicFunction_3=SymbolicFunction_p<3>;
using SymbolicFunction_4=SymbolicFunction_p<4>;
using SymbolicFunction_5=SymbolicFunction_p<5>;
#endif //AUTOMATICPROVER_SYMBOLICFUNCTION_H
