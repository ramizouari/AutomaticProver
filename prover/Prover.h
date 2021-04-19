//
// Created by ramizouari on 19/04/2021.
//

#ifndef AUTOMATICPROVER_PROVER_H
#define AUTOMATICPROVER_PROVER_H
#include "system/System.h"
#include <unordered_set>

class Prover
{
    std::unordered_set<Clause> T;
public:
    virtual ~Prover();
    virtual void prove_inconsistency(const System &A)=0;
};


#endif //AUTOMATICPROVER_PROVER_H
