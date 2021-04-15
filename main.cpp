#include <iostream>
#include "system/System.h"
#include "factory/VariableFactory.h"

/*
 * Example:
 * All humans are mortals;
 * Socrate is human
 * is Socrate Mortal?
 * */

int main() {
    VariableFactory factory;
    auto X=factory.new_instance();
    SymbolicPredicate *mortal_s = new SymbolicPredicate(1);
    SymbolicPredicate *human_s=new SymbolicPredicate(1);
    SymbolicConstant  *socrate = new SymbolicConstant,*aplaton=new SymbolicConstant;
    Predicate mortal(mortal_s,{X});
    Predicate human(human_s,{X});
    //All Humans are mortal
    Clause C1({mortal,~human});
    //Socrate is Human
    Clause C2({Predicate(human_s,{socrate})});
    //Socrate is not mortal
    Clause C3({~Predicate(mortal_s,{socrate})});
    System S({C1,C2,C3},factory);
    std::cout << "Can Socrate be immortal?: ";
    std::cout << std::boolalpha <<S.check_consistency();
    return 0;
}
