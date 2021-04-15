//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_LITERAL_H
#define AUTOMATICPROVER_LITERAL_H
#include "Variable.h"
#include "SymbolicFunction.h"
#include <vector>
#include <random>
#include <variant>

class Literal {
    Symbol *S;
    std::vector<Literal> args;
    friend class std::hash<Literal>;
    friend class VariableFactory;
public:
    Literal();
    Literal(Variable *v);
    Literal(Symbol *f,const std::vector<Literal> &_args);
    Literal(SymbolicConstant *c);
    bool operator!=(Literal L) const;
    bool operator==(Literal L) const;
    bool contains(Symbol *s) const;
    bool contains(const Literal &s) const;
    bool is_empty() const;
    void rename (Symbol *x,Symbol *y);
    void rename(const Literal &x,const Literal &y);
    bool operator==(const Literal &c);
    bool operator!=(const Literal &c);
    bool is_variable() const;
    int count_variables() const;
};

template<>
struct std::hash<Literal>
{
    inline static std::hash<Symbol*> H={};
    std::size_t operator()(Literal const& s) const noexcept
    {
        std::size_t h=0;
        for(auto l:s.args) h+=this->operator()(l);
        return h+H(s.S);
    }
};
#endif //AUTOMATICPROVER_LITERAL_H
