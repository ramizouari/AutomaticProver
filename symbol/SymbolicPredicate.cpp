//
// Created by ramizouari on 14/04/2021.
//

#include "SymbolicPredicate.h"

SymbolicPredicate::SymbolicPredicate(int _n) :n(_n){

}

int SymbolicPredicate::arg_count() {
    return n;
}

bool SymbolicPredicate::is_variable() {
    return false;
}


