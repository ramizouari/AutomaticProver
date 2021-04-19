//
// Created by ramizouari on 13/04/2021.
//

#include "Clause.h"
#include "system/System.h"
int Clause::count_variables() const {
    int R=0;
    for(const auto &P:predicates) R=std::max(R,P.count_variables());
    return R;
}

bool Clause::is_empty() const {
    return predicates.empty();
}

Clause::Clause(const std::vector<Predicate>&P):predicates(P) {

}

bool Clause::operator!=(Clause C)const {
    return predicates!=C.predicates;
}

bool Clause::operator==(Clause C)const {
    return !(predicates!=C.predicates);
}

void Clause::rename(Symbol *x, Symbol *y) {
    for(auto &p:predicates)
        p.rename(x,y);
}

void Clause::rename(Literal x, Literal y) {
    for(auto &p:predicates)
        p.rename(x,y);
}

int Clause::count_predicates() const {
    return predicates.size();
}

Clause Clause::operator|(Predicate c)const {
    Clause S(*this);
    S.predicates.push_back(c);
    return S;
}

Clause Clause::operator|(Clause c)const {
    Clause S(*this);
    for(int i=0;i<c.count_predicates();i++)
        S.predicates.push_back(c.predicates[i]);
    return S;
}

Clause::Clause(Predicate P):predicates{P} {

}

std::string Clause::get_name()
{
    std::string R;
    int n=predicates.size();
    if(n>0)
    {
        for(int i=0;i<n-1;i++)
            R+=predicates[i].get_name()+"|";
        R+=predicates.back().get_name();
    }
    return R;
}


std::optional<Literal> pgu(Literal a, Literal b, Predicate &E, Predicate &F, Clause &C, Clause &D)
{
    if(a==b)
        return a;
    else if(!a.is_variable() && !b.is_variable())
        return std::nullopt;
    else if(a.is_variable() && b.is_variable())
    {
        auto p = dynamic_cast<Variable*>(a.get()),q=dynamic_cast<Variable*>(b.get());
        if(p->variable_id() > q->variable_id())
        {
            C.rename(a,b);
            D.rename(a,b);
            E.rename(a,b);
            F.rename(a,b);
            return a;
        }
        else
        {
            C.rename(b,a);
            D.rename(b,a);
            E.rename(b,a);
            F.rename(b,a);
            return b;
        }
    }
    else if(a.is_variable())
    {
        if(b.contains(a))  return std::nullopt;
        C.rename(a,b);
        D.rename(a,b);
        E.rename(a,b);
        F.rename(a,b);
        return b;
    }
    else
    {
        if(a.contains(b)) return std::nullopt;
        C.rename(b,a);
        D.rename(b,a);
        E.rename(b,a);
        F.rename(b,a);
        return a;
    }
}

std::optional<Predicate> pgu(Predicate P1,Predicate P2,Clause &C1,Clause &C2)
{
    if(!Predicate::symbolically_same(P1,P2) ||P1.count_args()!=P2.count_args())
        return std::nullopt;
    for(int i=0;i<P1.count_args();i++)
    {
        Literal L1=P1.get_args()[i],L2=P2.get_args()[i];
        auto L= pgu(L1,L2,P1,P2,C1,C2);
        if(!L.has_value()) return std::nullopt;
    }
    return P1;
}

bool unifiable(Predicate P1,Predicate P2)
{

    Clause C1,C2;
    return pgu(P1,P2,C1,C2).has_value();
}

std::size_t std::hash<Clause>::operator()(const Clause &s) const noexcept {
    std::size_t h=0;
    for(const auto &p:s.predicates) h+=H(p);
    return h;
}