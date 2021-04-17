//
// Created by ramizouari on 14/04/2021.
//

#ifndef AUTOMATICPROVER_SYSTEM_H
#define AUTOMATICPROVER_SYSTEM_H


#include "../predicate/Clause.h"
#include "unordered_set"
#include <queue>
#include "../factory/VariableFactory.h"
#include <list>

class System
{
    bool consistent=true;
    std::vector<Clause> S;
    std::unordered_set<Clause> T;
    bool prove(Clause C1,Clause C2,std::queue<Clause>&Q);
    int clause_count_limit=1e6;
    int clause_count;
    VariableFactory &F;
public:
    System(const std::vector<Clause> &_S,VariableFactory &F);
    void add_clause(Clause C);
    bool prove(Clause C1,Clause C2);
    void rename_all(VariableFactory F);
    bool check_consistency();
    bool is_consistent() const;
    bool is_theorem(Clause C) const;
    std::vector<Clause> get_theorems() ;
};


#endif //AUTOMATICPROVER_SYSTEM_H
