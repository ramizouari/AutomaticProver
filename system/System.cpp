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

std::vector<Clause> System::get_hypotheseses()const  {
    return S;
}


void System::add_clause(Clause C)
{
    S.push_back(C);
}