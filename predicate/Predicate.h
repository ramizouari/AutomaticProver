//
// Created by ramizouari on 14/04/2021.
//

#ifndef AUTOMATICPROVER_PREDICATE_H
#define AUTOMATICPROVER_PREDICATE_H
#include "symbol/Literal.h"
class Clause;
class Predicate;
class SymbolicPredicate :virtual public Symbol{
    const int n;
public:
    SymbolicPredicate(int _n);
    virtual int arg_count() override;
    virtual bool is_variable() override;
    template<typename ...T>
    Predicate operator()(T ... s) const ;
};

template<int p>
class SymbolicPredicate_p: public SymbolicPredicate
{
public:
    SymbolicPredicate_p(): SymbolicPredicate(p){}
    template<typename ...T>
    Predicate operator()(T ... s) const requires (sizeof...(T)==p);
};
using SymbolicPreposition=SymbolicPredicate_p<0>;
using SymbolicPredicate_1=SymbolicPredicate_p<1>;
using SymbolicPredicate_2=SymbolicPredicate_p<2>;
using SymbolicPredicate_3=SymbolicPredicate_p<3>;

class Predicate : virtual public Identifiable<std::string>{
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

    template<typename ...T>
    Predicate(SymbolicPredicate_p<sizeof...(T)>*c,T ...K):P(c),args{K...},negated(false)
    {
    }

    Predicate();
    const std::vector<Literal> get_args() const;
    Predicate operator~() const;
    bool is_empty() const;
    int count_args() const;
    void rename(Symbol *x,Symbol *y);
    void rename(Literal a,Literal b);
    int count_variables() const;
    Clause operator|(Predicate C) const;
    Clause operator|(Clause c) const;
    std::string get_name() override;
    Variable* find_first_variable() const;
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

template<typename ...T>
inline Predicate SymbolicPredicate::operator()(T ... s) const
{
    std::vector<Literal> args{s...};
    return Predicate(const_cast<SymbolicPredicate*>(this),args);
}

template<int p> template<typename ...T>
inline Predicate SymbolicPredicate_p<p>::operator()(T ... s) const requires (sizeof...(T)==p)
{
    return Predicate(const_cast<SymbolicPredicate_p<p>*>(this),s...);
}

#endif //AUTOMATICPROVER_PREDICATE_H
