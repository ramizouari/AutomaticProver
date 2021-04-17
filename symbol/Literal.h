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
#include "IdentifiedSymbol.h"

class Literal : virtual public Identifiable<std::string> {
protected:
    Symbol *S;
    std::vector<Literal> args;
    friend class std::hash<Literal>;
    friend class VariableFactory;
public:
    Literal();
    Literal(Variable *v);
    Literal(Symbol *f,const std::vector<Literal> &_args={});
    template<typename T>
    Literal(SymbolicFunction_p<1>*c,T K);
    template<typename T1,typename T2>
    Literal(SymbolicFunction_p<2>*c,T1 K1,T2 K2);
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
    Symbol* get();
    int count_variables() const;

    std::string get_name() override
    {
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
