//
// Created by ramizouari on 19/04/2021.
//

#ifndef AUTOMATICPROVER_SYSTEM_H
#define AUTOMATICPROVER_SYSTEM_H
#include "predicate/Clause.h"
#include <vector>
class System {
protected:
    std::vector<Clause> S;
    std::vector<Clause> G;
    System();
public:
    System(const std::vector<Clause> &_S);
    virtual ~System()=0;
    virtual bool check_consistency()=0;
    const std::vector<Clause>& get_hypotheseses() const;
    const std::vector<Clause>& get_goals() const;
    virtual std::vector<Clause> get_theorems()=0 ;
    void add_clause(Clause C);
    void add_goal(Clause C);

};


#endif //AUTOMATICPROVER_SYSTEM_H
