//
// Created by ramizouari on 20/04/2021.
//

#ifndef AUTOMATICPROVER_COMMUTATIVERING_H
#define AUTOMATICPROVER_COMMUTATIVERING_H
#include "Ring.h"

class CommutativeRing :public Ring{
public:
    CommutativeRing(IdentifiedVariableFactory<std::string> &F);
};


#endif //AUTOMATICPROVER_COMMUTATIVERING_H
