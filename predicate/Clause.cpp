//
// Created by ramizouari on 13/04/2021.
//

#include "Clause.h"
#include "system/PredicateSystem.h"
#include <stack>
#include <functional>
#include <unordered_map>
#include "symbol/Substitution.h"
#include <algorithm>

int Clause::count_variables() const {
    int R=0;
    std::stack<Literal> Q;
    for(auto p:predicates) for(auto L:p.get_args())
        Q.push(L);
    std::unordered_set<Variable*> v_set;
    while(!Q.empty())
    {
        auto w = Q.top();
        if(w.get()->is_variable())
            v_set.insert(dynamic_cast<Variable*>(w.get()));
        Q.pop();
        for(const auto &u:w.get_args())
            Q.push(u);

    }
    return v_set.size();
}

bool Clause::is_empty() const {
    return predicates.empty();
}

Clause::Clause(const std::deque<Predicate>&P):predicates(P)
{
    to_normal_form();
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
    return S|=c;
}

Clause Clause::operator|(Clause c)const {
    Clause S(*this);
    return S|=c;
}

Clause::Clause(Predicate P):predicates{P} {
    to_normal_form();
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

Variable *Clause::find_first_variable() const {
    for(auto P:predicates) if(auto V=P.find_first_variable())
        return V;
    return nullptr;
}


std::optional<Literal> pgu(Literal a, Literal b,Literal&A,Literal&B, Predicate &E, Predicate &F, Clause &C, Clause &D)
{
    if(a==b)
        return a;
    else if(!a.is_variable() && !b.is_variable())
    {
        if(a.get()==b.get())
        {
            int n=a.get_args().size();
            std::vector<Literal> args;
            for(int i=0;i<n;i++)
            {
                auto S=pgu(a.get_args()[i],b.get_args()[i],a,b,E,F,C,D);
                if(!S.has_value())
                    return std::nullopt;
                args.push_back(S.value());
            }
            return Literal(a.get(),args);
        }
        else return std::nullopt;
    }
    else if(a.is_variable() && b.is_variable())
    {
        auto p = dynamic_cast<Variable*>(a.get()),q=dynamic_cast<Variable*>(b.get());
        if(p->variable_id() > q->variable_id())
        {
            C.rename(a,b);
            D.rename(a,b);
            E.rename(a,b);
            F.rename(a,b);
            A.rename(a,b);
            B.rename(a,b);
            return a;
        }
        else
        {
            C.rename(b,a);
            D.rename(b,a);
            E.rename(b,a);
            F.rename(b,a);
            A.rename(b,a);
            B.rename(b,a);
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
        A.rename(a,b);
        B.rename(a,b);
        return b;
    }
    else
    {
        if(a.contains(b)) return std::nullopt;
        C.rename(b,a);
        D.rename(b,a);
        E.rename(b,a);
        F.rename(b,a);
        A.rename(b,a);
        B.rename(b,a);
        return a;
    }
}
using couple=std::pair<Symbol*,Literal>;
struct LiteralWrapper
{
    Literal s;
    LiteralWrapper():s(nullptr,{}){}
    LiteralWrapper(Literal _s):s(_s){}
    operator Literal()
    {
        return s;
    }
};
using LiteralRef=std::reference_wrapper<Literal>;
std::optional<Substitution> pgu(Literal a, Literal b)
{
    using Literal_couple = std::tuple<Literal,Literal>;
    std::queue<Literal_couple> L;
    Substitution sigma;
    Literal c(a);
    L.push({a,b});
    while(!L.empty())
    {
        auto [u,v]=L.front();
        L.pop();
        if(u.is_variable() && sigma.contains(dynamic_cast<Variable*>(u.get())))
            sigma(u);
        if(v.is_variable() && sigma.contains(dynamic_cast<Variable*>(v.get())))
            sigma(v);

        if(!u.is_variable()&&!v.is_variable())
        {
            if(u.get()!=v.get())
                return std::nullopt;
            else if(u.get_args().size()!=v.get_args().size())
                throw std::logic_error("two identical symbols must have the same arity");
            int n=u.get_args().size();
            for(int i=0;i<n;i++)
                L.push({u.get_args()[i],v.get_args()[i]});
        }
        else if(u.is_variable())
        {
            if(v.contains(u))
                return std::nullopt;
            sigma.add_substitution(dynamic_cast<Variable*>(u.get()),v);
        }
        else
        {
            if(u.contains(v))
                return std::nullopt;
            sigma.add_substitution(dynamic_cast<Variable*>(v.get()),u);
        }
    }
    return sigma;
}


std::optional<Substitution> pgu(Predicate P1,Predicate P2)
{
    Substitution sigma;
    int n=P1.count_args();
    if(!Predicate::symbolically_same(P1,P2))
        return std::nullopt;
    else for(int i=0;i<n;i++)
    {
        auto phi=pgu(P1.get_args()[i],P2.get_args()[i]);
        if(!phi.has_value())
            return std::nullopt;
        for(const auto &[v,L]:phi.value().get())
        {
            if (sigma.contains(v))
            {
                auto Q=sigma.get(v);
                if (Q.is_variable())
                    sigma.try_add_substitution(dynamic_cast<Variable*>(Q.get()),L);
                else if (L != sigma.get(v))
                    return std::nullopt;
            }
            else sigma.try_add_substitution(v,L);
        }
    }
    return sigma;
}


std::optional<Predicate> pgu(Predicate P1,Predicate P2,Clause &C1,Clause &C2)
{
    if(!Predicate::symbolically_same(P1,P2) ||P1.count_args()!=P2.count_args())
        return std::nullopt;
    for(int i=0;i<P1.count_args();i++)
    {
        Literal L1=P1.get_args()[i],L2=P2.get_args()[i];
        auto L= pgu(L1,L2,L1,L2,P1,P2,C1,C2);
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

const std::deque<Predicate>& Clause::get_args() const
{
    return predicates;
}


std::deque<Predicate>& Clause::get_args()
{
    return predicates;
}

void Clause::to_normal_form()
{

    std::deque<Predicate> A;
    for(auto c:predicates) if(!c.is_negation())
        A.push_back(c);
    affirmations=A.size();
    for(auto c:predicates) if(c.is_negation())
            A.push_back(c);
    predicates=std::move(A);
}

int Clause::count_affirmation() const
{
    return affirmations;
}

Clause &Clause::operator|=(Clause a)
{
    for(int i=0;i<a.count_predicates();i++)
        if(a.predicates[i].is_negation())
            predicates.push_back(a.predicates[i]);
        else {
            predicates.push_front(a.predicates[i]);
            affirmations++;
        }
    return *this;
}

Clause &Clause::operator|=(Predicate a)
{
        if(a.is_negation())
            predicates.push_back(a);
        else {
            predicates.push_front(a);
            affirmations++;
        }
    return *this;
}
