//
// Created by ramizouari on 21/04/2021.
//

#ifndef AUTOMATICPROVER_SUBSTITUTION_H
#define AUTOMATICPROVER_SUBSTITUTION_H
#include <unordered_map>
#include <vector>
#include "Literal.h"
#include "Variable.h"
#include <unordered_set>
class Predicate;
class Clause;
class Substitution
{
    using VariableRename=std::pair<Variable*,Literal>;
    std::vector<VariableRename> S;
    std::unordered_map<Variable*,int> V;
    bool in_normal_form=true;
public:
    void add_substitution(Variable *s,Literal A);
    bool try_add_substitution(Variable *s,Literal A);
    void to_normal_form();
    void operator()(Literal &A);
    void operator()(Predicate &A);
    void operator()(Clause &A);
    Literal operator()(Variable *s);
    bool contains(Variable *v) const;
    const std::vector<VariableRename> get() const;
    Literal get(Variable *S) const;
};


#endif //AUTOMATICPROVER_SUBSTITUTION_H
