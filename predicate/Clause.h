//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_CLAUSE_H
#define AUTOMATICPROVER_CLAUSE_H
#include <vector>
#include "Predicate.h"
class System;
class Clause : virtual public Identifiable<std::string>{
    std::vector<Predicate> predicates;
    friend class System;
    friend class std::hash<Clause>;
    friend class VariableFactory;
public:
    bool operator!=(Clause C) const;
    bool operator==(Clause C) const;
    Clause(const std::vector<Predicate> &P={});
    Clause(Predicate P);
    Clause operator|(Clause a) const;
    Clause operator|(Predicate a) const;
    int count_variables() const;
    int count_predicates() const;
    bool is_empty() const;
    void rename(Symbol *x,Symbol *y);
    void rename(Literal a,Literal b);
    std::string get_name() override;
    Variable* find_first_variable() const;
};

std::optional<Literal> pgu(Literal a,Literal b,Predicate &E,Predicate &F,Clause &C,Clause &D);

std::optional<Predicate> pgu(Predicate P1,Predicate P2,Clause &C1,Clause &C2);

bool unifiable(Predicate P1,Predicate P2);


template<>
struct std::hash<Clause>
{
    inline static  std::hash<Predicate> H={};
    std::size_t operator()(Clause const& s) const noexcept;
};

#endif //AUTOMATICPROVER_CLAUSE_H
