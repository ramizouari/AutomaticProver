//
// Created by ramizouari on 19/04/2021.
//

#ifndef AUTOMATICPROVER_HERBRANDPROVER_H
#define AUTOMATICPROVER_HERBRANDPROVER_H
#include "Prover.h"

class HerbrandProver:public Prover {

    std::vector<Literal> H;
    std::vector<std::reference_wrapper<SymbolicFunction>> F_set;
    std::vector<SymbolicConstant*> K_set;
    std::vector<Clause> C_set;
    std::vector<Clause> A;
    int n=0;
    void initialize(const System &A);
    void augment();
public:
    void prove_inconsistency(const System &A) override;
};


#endif //AUTOMATICPROVER_HERBRANDPROVER_H
