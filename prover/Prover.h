//
// Created by ramizouari on 19/04/2021.
//

#ifndef AUTOMATICPROVER_PROVER_H
#define AUTOMATICPROVER_PROVER_H
#include "system/PredicateSystem.h"
#include <unordered_set>

class Prover
{
    std::unordered_set<Clause> T;
public:
    virtual ~Prover();
    virtual bool prove_inconsistency(const PredicateSystem &A)=0;
};


#endif //AUTOMATICPROVER_PROVER_H
