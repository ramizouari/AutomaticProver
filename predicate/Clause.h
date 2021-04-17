//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_CLAUSE_H
#define AUTOMATICPROVER_CLAUSE_H
#include <vector>
#include "Predicate.h"

class Clause {
    std::vector<Predicate> predicates;
    friend class System;
    friend class std::hash<Clause>;
    friend class VariableFactory;
public:
    bool operator!=(Clause C) const;
    bool operator==(Clause C) const;
    Clause(const std::vector<Predicate> &P={});
    int count_variables() const;
    int count_predicates() const;
    bool is_empty() const;
    void rename(Symbol *x,Symbol *y);
    void rename(Literal a,Literal b);

};

inline Literal pgu(Literal a,Literal b,Predicate &E,Predicate &F,Clause &C,Clause &D)
{
    if(a==b)
        return a;
    else if(!a.is_variable() && !b.is_variable())
        return {};
    else if(a.is_variable() && b.is_variable())
    {
        auto p = dynamic_cast<Variable*>(a.get()),q=dynamic_cast<Variable*>(b.get());
        if(p->variable_id() > q->variable_id())
        {
            C.rename(a,b);
            D.rename(a,b);
            return a;
        }
        else
        {
            C.rename(b,a);
            D.rename(b,a);
            return b;
        }
    }
    else if(a.is_variable())
    {
        if(b.contains(a))  return {};
        C.rename(a,b);
        D.rename(a,b);
        return b;
    }
    else if(b.is_variable())
    {
        if(a.contains(b)) return {};
        C.rename(b,a);
        D.rename(b,a);
        return a;
    }

}

inline Predicate pgu(Predicate P1,Predicate P2,Clause &C1,Clause &C2)
{
    if(!Predicate::symbolically_same(P1,P2) ||P1.count_args()!=P2.count_args())
        return {};
    for(int i=0;i<P1.count_args();i++)
    {
        Literal L1=P1.get_args()[i],L2=P2.get_args()[i];
        Literal L= pgu(L1,L2,P1,P2,C1,C2);
        if(L.is_empty()) return {};
    }
    return P1;
}


template<>
struct std::hash<Clause>
{
    inline static  std::hash<Predicate> H={};
    std::size_t operator()(Clause const& s) const noexcept
    {
        std::size_t h=0;
        for(const auto &p:s.predicates) h+=H(p);
        return h;
    }
};

#endif //AUTOMATICPROVER_CLAUSE_H
