//
// Created by ramizouari on 19/04/2021.
//

#ifndef AUTOMATICPROVER_PREPOSITIONALSYSTEM_H
#define AUTOMATICPROVER_PREPOSITIONALSYSTEM_H
#include "System.h"

class PrepositionalSystem :public System{
public:
    PrepositionalSystem(const std::vector<Clause> &_S);
};


#endif //AUTOMATICPROVER_PREPOSITIONALSYSTEM_H
