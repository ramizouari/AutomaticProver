//
// Created by ramizouari on 19/04/2021.
//

#ifndef AUTOMATICPROVER_PREPOSITIONALSYSTEM_H
#define AUTOMATICPROVER_PREPOSITIONALSYSTEM_H
#include "System.h"
#include <vector>
#include <queue>
#include <unordered_set>

class PrepositionalSystem :public System{
    bool prove(Clause C1,Clause C2,std::queue<Clause>&Q);
    bool consistent=true;
    int clause_count=0;
    int clause_count_limit=1e6;
    std::unordered_set<Clause> T;
public:
    PrepositionalSystem(const std::vector<Clause> &_S);
    bool check_consistency() override;
    std::vector<Clause> get_theorems() override;
};


#endif //AUTOMATICPROVER_PREPOSITIONALSYSTEM_H
