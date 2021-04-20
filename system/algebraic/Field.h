//
// Created by ramizouari on 20/04/2021.
//

#ifndef AUTOMATICPROVER_FIELD_H
#define AUTOMATICPROVER_FIELD_H
#include "IntegralRing.h"

class Field :public IntegralRing
{
    IdentifiedSymbolicFunction_1<std::string> mult_inverse;
public:
    Field(IdentifiedVariableFactory<std::string> &F);
};


#endif //AUTOMATICPROVER_FIELD_H
