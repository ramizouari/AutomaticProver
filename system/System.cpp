//
// Created by ramizouari on 19/04/2021.
//

#include "System.h"
#include "symbol/SymbolicPredicate.h"
#include "symbol/Variable.h"
#include <unordered_set>
#include <queue>

System::~System() {

}

System::System(const std::vector<Clause> &_S):S(_S) {

}

System::System() {

}

const std::vector<Clause>& System::get_hypotheseses()const  {
    return S;
}


void System::add_clause(Clause C)
{
    S.push_back(C);
}

void System::add_goal(Clause C) {
    add_clause(C);
    G.push_back(C);
}

const std::vector<Clause>& System::get_goals() const {
    return G;
}
