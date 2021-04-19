//
// Created by ramizouari on 14/04/2021.
//

#ifndef AUTOMATICPROVER_SYSTEM_H
#define AUTOMATICPROVER_SYSTEM_H


#include "predicate/Clause.h"
#include "unordered_set"
#include <queue>
#include "factory/VariableFactory.h"
#include <list>

class System
{
protected:
    bool consistent=true;
    std::vector<Clause> S;
    std::unordered_set<Clause> T;
    bool prove(Clause C1,Clause C2,std::queue<Clause>&Q);
    int clause_count_limit=1e6;
    int clause_count=0;
    VariableFactory &F;
    System(VariableFactory &F);
public:
    System(const std::vector<Clause> &_S,VariableFactory &F);
    void add_clause(Clause C);
    bool prove(Clause C1,Clause C2);
    void rename_all();
    bool check_consistency();
    void merge(System S);
    void merge(Predicate P);
    void merge(Clause C);
    bool is_consistent() const;
    bool is_theorem(Clause C) const;
    void set_limit(int L);
    System operator&(System S) const;
    System& operator&=(System S);
    System& operator&=(Clause C);
    System& operator&=(Predicate P);
    System operator&(Clause C) const;
    System operator&(Predicate P) const;
    std::vector<Clause> get_hypotheseses() const;
    std::vector<Clause> get_theorems() ;
    std::vector<SymbolicFunction*> get_functions() const;
};



#endif //AUTOMATICPROVER_SYSTEM_H
