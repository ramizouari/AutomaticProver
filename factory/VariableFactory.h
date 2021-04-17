//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_VARIABLEFACTORY_H
#define AUTOMATICPROVER_VARIABLEFACTORY_H
#include "../symbol/Variable.h"
#include "../predicate/Clause.h"
#include <unordered_map>

class VariableFactory {
protected:
    inline static std::unordered_map<int,Variable*> S_map;
    inline static std::unordered_map<Variable*,int> id_map;
    inline static int counter=0;
    void resize(int s);
public:
    VariableFactory();
    VariableFactory(VariableFactory &);
    VariableFactory(VariableFactory &&);
    ~VariableFactory();
    Variable* by_id(int id) const;
    int id_of(Variable *S);
    Variable* new_instance();
    int rename(Literal &L,int offset);
    int rename(Clause &C,int offset);
};


#endif //AUTOMATICPROVER_VARIABLEFACTORY_H
