//
// Created by ramizouari on 22/04/2021.
//

#ifndef AUTOMATICPROVER_RESOLUTIONPROVER_H
#define AUTOMATICPROVER_RESOLUTIONPROVER_H
#include "Prover.h"

class ResolutionProver:public Prover
{
protected:
    int clause_count=0;
    int clause_count_limit=1e6;
    bool consistent=true;
public:
    virtual bool prove_inconsistency(const PredicateSystem &A);
    virtual void prove(const Clause &A,const Clause &B, std::queue<Clause> &Q);
    void set_limit(int L);
    std::vector<Clause> get_theorems() const;
};


#endif //AUTOMATICPROVER_RESOLUTIONPROVER_H
