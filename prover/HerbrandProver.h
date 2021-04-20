//
// Created by ramizouari on 19/04/2021.
//

#ifndef AUTOMATICPROVER_HERBRANDPROVER_H
#define AUTOMATICPROVER_HERBRANDPROVER_H
#include "Prover.h"
#include "symbol/SymbolicFunction.h"
#include <functional>

class HerbrandProver:public Prover {

    std::vector<Literal> H;
    std::vector<std::vector<Literal>> H_construction;
    std::vector<std::reference_wrapper<SymbolicFunction>> F_set;
    std::vector<SymbolicConstant*> K_set;
    std::vector<Clause> C_set;
    std::vector<Clause> A;
    int n=5;
    void initialize(const PredicateSystem &A);
    void augment();
public:
    bool prove_inconsistency(const PredicateSystem &A) override;
};


#endif //AUTOMATICPROVER_HERBRANDPROVER_H
