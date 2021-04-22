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
    if(S==x.S)
    {
        S = y.S;
        args=y.args;
    }
    else for(auto &L:args) L.rename(x,y);
}

int Literal::count_variables() const {
    int R=0;
    std::stack<Literal> Q;
    Q.push(*this);
    std::unordered_set<Variable*> v_set;
    while(!Q.empty())
    {
        auto w = Q.top();
        if(w.S->is_variable())
            v_set.insert(dynamic_cast<Variable*>(w.S));
        Q.pop();
        for(const auto &u:w.args)
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


Symbol* Literal::get() const{
    return S;
}

std::vector<Literal>& Literal::get_args()
{
    return args;
}

std::string Literal::get_name() {
    if(!S)
        return "??";
    std::string R=dynamic_cast<IdentifiableSymbol<std::string>*>(S)->get_name();
    int n=args.size();
    if(n>0)
    {
        R += '(';
        for (int i = 0; i < n - 1; i++)
            R += args[i].get_name() + ", ";

        R+= args.back().get_name();
        R+=')';
    }
    return R;
}

Variable *Literal::find_first_variable() {
    if(S->is_variable())
        return dynamic_cast<Variable*>(S);
    else for(auto u:args) if(auto V=u.find_first_variable())
        return V;
    return nullptr;
}



