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
    System();
public:
    System(const std::vector<Clause> &_S);
    virtual ~System()=0;
    virtual bool check_consistency()=0;
    std::vector<Clause> get_hypotheseses() const;
    virtual std::vector<Clause> get_theorems()=0 ;
    void add_clause(Clause C);

};


#endif //AUTOMATICPROVER_SYSTEM_H
