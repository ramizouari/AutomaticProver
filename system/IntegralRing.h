//
// Created by ramizouari on 20/04/2021.
//

#ifndef AUTOMATICPROVER_INTEGRALRING_H
#define AUTOMATICPROVER_INTEGRALRING_H
#include "CommutativeRing.h"

class IntegralRing:public CommutativeRing {
public:
    IntegralRing(IdentifiedVariableFactory<std::string> &F);

};


#endif //AUTOMATICPROVER_INTEGRALRING_H
