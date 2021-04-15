//
// Created by ramizouari on 13/04/2021.
//

#include "SymbolicFunction.h"

int SymbolicFunction::arg_count() {
    return n;
}

bool SymbolicFunction::is_variable() {
    return false;
}

SymbolicFunction::SymbolicFunction(int _n) :n(_n){

}
