//
// Created by ramizouari on 14/04/2021.
//

#ifndef AUTOMATICPROVER_PREDICATESYSTEM_H
#define AUTOMATICPROVER_PREDICATESYSTEM_H


#include "predicate/Clause.h"
#include "unordered_set"
#include <queue>
#include "factory/VariableFactory.h"
#include <list>
#include "System.h"
class Prover;
class PredicateSystem:public System
{
protected:
    bool consistent=true;
    std::unordered_set<Clause> T;
    bool prove(Clause C1,Clause C2,std::queue<Clause>&Q);
    int clause_count_limit=1e6;
    int clause_count=0;
    VariableFactory &F;
    PredicateSystem(VariableFactory &F);
public:
    PredicateSystem(const std::vector<Clause> &_S,VariableFactory &F);
    bool prove(Clause C1,Clause C2);
    void rename_all();
    bool check_consistency();
    bool check_consistency(Prover &P);
    void merge(PredicateSystem S);
    void merge(Predicate P);
    void merge(Clause C);
    bool is_consistent() const;
    bool is_theorem(Clause C) const;
    void set_limit(int L);
    PredicateSystem operator&(PredicateSystem S) const;
    PredicateSystem& operator&=(PredicateSystem S);
    PredicateSystem& operator&=(Clause C);
    PredicateSystem& operator&=(Predicate P);
    PredicateSystem operator&(Clause C) const;
    PredicateSystem operator&(Predicate P) const;
    std::vector<SymbolicFunction*> get_functions() const;
    std::vector<Clause> get_theorems() override;

};



#endif //AUTOMATICPROVER_PREDICATESYSTEM_H
