//
// Created by ramizouari on 20/04/2021.
//

#ifndef AUTOMATICPROVER_RING_H
#define AUTOMATICPROVER_RING_H
#include "system/algebraic/CommutativeGroup.h"

class Ring :public CommutativeGroup{
protected:
    IdentifiedSymbolicConstant<std::string> _1;
    IdentifiedSymbolicFunction_2<std::string> product;
public:
    Ring(IdentifiedVariableFactory<std::string> &F);
};


#endif //AUTOMATICPROVER_RING_H
