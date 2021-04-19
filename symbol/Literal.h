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
#include <optional>
#include <initializer_list>

class Literal;

class SymbolicFunction : virtual public Symbol
{
    const int n;
public:
    SymbolicFunction(int _n);
    virtual int arg_count() override;
    virtual bool is_variable() override;
    template<typename ...T>
    Literal operator()(T ... s) const;
};

template<int p>
class SymbolicFunction_p: public SymbolicFunction
{
public:
    SymbolicFunction_p(): SymbolicFunction(p){}
    template<typename ...T>
    Literal operator()(T ... s) const requires (sizeof...(T)==p);
};
using SymbolicConstant=SymbolicFunction_p<0>;
using SymbolicFunction_1=SymbolicFunction_p<1>;
using SymbolicFunction_2=SymbolicFunction_p<2>;
using SymbolicFunction_3=SymbolicFunction_p<3>;
using SymbolicFunction_4=SymbolicFunction_p<4>;
using SymbolicFunction_5=SymbolicFunction_p<5>;


class Literal : virtual public Identifiable<std::string> {
protected:
    Symbol *S;
    std::vector<Literal> args;
    friend class std::hash<Literal>;
    friend class VariableFactory;
public:
    Literal(Variable *v);
    Literal(Symbol *f,const std::vector<Literal> &_args={});

    template<typename ...T>
    Literal(SymbolicFunction_p<sizeof...(T)>*c,T ...K):S(c),args{Literal(K)...}
    {
    }

    bool operator!=(Literal L) const;
    bool operator==(Literal L) const;
    bool contains(Symbol *s) const;
    bool contains(const Literal &s) const;
    void rename (Symbol *x,Symbol *y);
    void rename(const Literal &x,const Literal &y);
    bool operator==(const Literal &c);
    bool operator!=(const Literal &c);
    bool is_variable() const;
    std::vector<Literal> get_args();
    Symbol* get();
    int count_variables() const;
    std::string get_name() override;
    Variable* find_first_variable();
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

template<typename ...T>
inline Literal SymbolicFunction::operator()(T ... s) const
{
    std::vector<Literal> args{Literal(s)...};
    return Literal(this,args);
}

template<int p> template<typename ...T>
inline Literal SymbolicFunction_p<p>::operator()(T ... s) const requires (sizeof...(T)==p)
{
    return Literal(const_cast<SymbolicFunction_p<p>*>(this),Literal(s)...);
}
#endif //AUTOMATICPROVER_LITERAL_H
