//
// Created by ramizouari on 14/04/2021.
//

#include "Predicate.h"
#include <stdexcept>

Predicate::Predicate(SymbolicPredicate *_P,const std::vector<Literal>&_args, bool _negated) :
P(_P),negated(_negated),args(_args)
{
    if(P->arg_count() != args.size())
        throw std::invalid_argument("predicate n-arity and arguments count do not match");
}

Predicate Predicate::operator~() const
{
    return Predicate(P,args,!negated);
}

bool Predicate::symbolically_negated(Predicate P1, Predicate P2) {
    return P1.P==P2.P && P1.negated!=P2.negated;
}

int Predicate::count_args() const {
    return args.size();
}

bool Predicate::symbolically_same(Predicate P1, Predicate P2)
{
    return P1.P==P2.P && P1.negated == P2.negated;
}

bool Predicate::symbolically_different(Predicate P1, Predicate P2) {
    return P1.P!=P2.P;
}

const std::vector<Literal> Predicate::get_args() const {
    return args;
}

void Predicate::rename(Symbol *x, Symbol *y)
{
    for(auto &s:args) s.rename(x,y);
}

void Predicate::rename(Literal a,Literal b)
{
    for(auto &s:args) s.rename(a,b);
}

bool Predicate::is_empty() const {
    return !P;
}

int Predicate::count_variables() const {
    int R=0;
    for(auto s:args) R=std::max(R,s.count_variables());
    return R;
}

bool Predicate::operator!=(Predicate predicate) const {
    return predicate.P!=P || predicate.negated!=negated||predicate.args!=args;
}


bool Predicate::operator==(Predicate predicate) const {
    return !(*this!=predicate);
}

Predicate::Predicate() :P(nullptr){

}
