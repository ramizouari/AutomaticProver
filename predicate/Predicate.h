//
// Created by ramizouari on 14/04/2021.
//

#ifndef AUTOMATICPROVER_PREDICATE_H
#define AUTOMATICPROVER_PREDICATE_H
#include "../symbol/Literal.h"
#include "../symbol/SymbolicPredicate.h"

class Predicate {
    SymbolicPredicate *P;
    std::vector<Literal> args;
    bool negated;
    friend class std::hash<Predicate>;
    friend class VariableFactory;
public:
    bool operator!=(Predicate P) const;
    bool operator==(Predicate P) const;
    static bool symbolically_negated(Predicate P1,Predicate P2);
    static bool symbolically_same(Predicate P1,Predicate P2);
    static bool symbolically_different(Predicate P1,Predicate P2);
    Predicate(SymbolicPredicate *_P,const std::vector<Literal> &_args={},bool _negated=false);
    Predicate(SymbolicPreposition *_P,bool _negated=false);

    template<typename T>
    Predicate(SymbolicPredicate_1 *_P,T k,bool _negated=false):P(_P),negated(_negated) {
        args.emplace_back(k);
    }

    Predicate();
    const std::vector<Literal> get_args() const;
    Predicate operator~() const;
    bool is_empty() const;
    int count_args() const;
    void rename(Symbol *x,Symbol *y);
    void rename(Literal a,Literal b);
    int count_variables() const;
};


template<>
struct std::hash<Predicate>
{
    inline static  std::hash<Literal> H_L={};
    inline static  std::hash<SymbolicPredicate*> H_S={};
    std::size_t operator()(Predicate const& s) const noexcept
    {
        std::size_t h=0;
        for(const auto& l:s.args) h+=H_L(l);
        if(s.negated) h=~h;
        return H_S(s.P)+h;
    }
};

#endif //AUTOMATICPROVER_PREDICATE_H
