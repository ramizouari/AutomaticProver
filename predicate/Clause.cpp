//
// Created by ramizouari on 13/04/2021.
//

#include "Clause.h"

int Clause::count_variables() const {
    int R=0;
    for(const auto &P:predicates) R=std::max(R,P.count_variables());
    return R;
}

bool Clause::is_empty() const {
    return predicates.empty();
}

Clause::Clause(const std::vector<Predicate>&P):predicates(P) {

}

bool Clause::operator!=(Clause C)const {
    return predicates!=C.predicates;
}

bool Clause::operator==(Clause C)const {
    return !(predicates!=C.predicates);
}

void Clause::rename(Symbol *x, Symbol *y) {
    for(auto &p:predicates)
        p.rename(x,y);
}

void Clause::rename(Literal x, Literal y) {
    for(auto &p:predicates)
        p.rename(x,y);
}

int Clause::count_predicates() const {
    return predicates.size();
}
