//
// Created by ramizouari on 21/04/2021.
//

#include "Substitution.h"
#include "exception/InvalidSubstitutionException.h"
#include "predicate/Predicate.h"
#include "predicate/Clause.h"

void Substitution::add_substitution(Variable *s, Literal A)
{
    if(!try_add_substitution(s,A))
        throw InvalidSubstitutionException();
}

void Substitution::operator()(Literal &A)
{
    if(!in_normal_form)
        to_normal_form();
    /*
     * Supposition:
     * - Substitution must be in normal form
     * */
    if(A.is_variable())
    {
        auto v=dynamic_cast<Variable*>(A.get());
        if(V.contains(v))

            A=S[V[v]].second;
    }
    else for(auto &B:A.get_args()) this->operator()(B);
}

void Substitution::operator()(Predicate &P)
{
    /*
     * Supposition:
     * - Substitution must be in normal form
     * */
    for(auto &L:P.get_args()) this->operator()(L);
}


void Substitution::operator()(Clause &C)
{
    /*
     * Supposition:
     * - Substitution must be in normal form
     * */
    for(auto &P:C.get_args()) this->operator()(P);
}

bool Substitution::try_add_substitution(Variable *s,Literal A)
{
    if(V.contains(s))
        return false;
    this->operator()(A);
    V.insert({s,S.size()});
    S.push_back({s,A});
    in_normal_form=false;
    return true;
}

bool Substitution::contains(Variable *v) const{
    return V.contains(v);
}

Literal Substitution::operator()(Variable *v) {
    Literal L(v);
    this->operator()(L);
    return L;
}

const std::vector<Substitution::VariableRename> Substitution::get()const {
    return S;
}

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

void Substitution::to_normal_form()
{
    Substitution phi;
    int n=S.size();
    for(int i=n-1;i>=0;i--)
    {
        Literal L=S[i].second;
        phi(L);
        phi.add_substitution(S[i].first,L);
        phi.in_normal_form=true;
    }
    V=std::move(phi.V);
    S=std::move(phi.S);
    in_normal_form=true;
}

Literal Substitution::get(Variable *u) const {
    return S[V.at(u)].second;
}
