//
// Created by ramizouari on 13/04/2021.
//

#include "Literal.h"
#include <unordered_set>
#include <stack>
#include <stdexcept>

Literal::Literal(Variable *v) :S(v){
}

Literal::Literal(Symbol *f,const std::vector<Literal>&_args):S(f),args(_args)
{
    if(f->arg_count() != args.size())
        throw std::invalid_argument("function n-arity and arguments count do not match");
}

bool Literal::contains(Symbol *s) const{
    if (S==s) return true;
    for(const auto &u:args) if(u.contains(s)) return true;
    return false;
}

Literal::Literal(): S(nullptr){

}

bool Literal::is_empty() const {
    return !S;
}

void Literal::rename(Symbol *x, Symbol *y) {
    if(S==x) S=y;
    else for(auto &L:args) L.rename(x,y);
}

bool Literal::operator==(const Literal &c) {
    return !(*this != c);
}

bool Literal::operator!=(const Literal &c) {
    return S!=c.S || args!=c.args;
}

bool Literal::is_variable() const {
    return S && S->is_variable();
}

bool Literal::contains(const Literal &s) const {
    return contains(s.S);
}

void Literal::rename(const Literal &x,const Literal& y) {
    rename(x.S,y.S);
}

int Literal::count_variables() const {
    int R=0;
    std::stack<Literal> Q;
    Q.push(*this);
    std::unordered_set<Variable*> v_set;
    while(!Q.empty())
    {
        auto w = Q.top();
        if(!w.is_empty() && w.S->is_variable())
            v_set.insert(dynamic_cast<Variable*>(w.S));
        Q.pop();
        for(const auto &u:args)
            Q.push(u);

    }
    return v_set.size();
}

bool Literal::operator==(Literal L) const {
    return !(*this != L);
}

bool Literal::operator!=(Literal L)const {
    return S!=L.S || args!=L.args;
}

Literal::Literal(SymbolicConstant *f):Literal(f,{}) {

}
