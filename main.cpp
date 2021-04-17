#include <iostream>
#include "system/System.h"
#include "factory/VariableFactory.h"
#include "symbol/IdentifiedSymbol.h"

/*
 * Example:
 * All humans are mortals;
 * Socrate is human
 * is Socrate Mortal?
 * */

int main() {
    VariableFactory factory;
    auto X=factory.new_instance();
    IdentifiedSymbolicPredicate<std::string> *mortal_s = new IdentifiedSymbolicPredicate<std::string>("mortal",1);
    IdentifiedSymbolicPredicate<std::string>  *human_s=new IdentifiedSymbolicPredicate<std::string> ("human",1);
    SymbolicPredicate *man_s= new IdentifiedSymbolicPredicate<std::string>("man",1);
    SymbolicConstant  *socrate = new IdentifiedSymbolicConstant<std::string>("socrate"),
            *aplaton=new IdentifiedSymbolicConstant<std::string>("platon");
    Predicate mortal(mortal_s,{X});
    Predicate human(human_s,{X});
    Predicate man(man_s,{X});
    //All Humans are mortal
    Clause C1({mortal,~human});
    //All mans are humans
    Clause C2({~man,human});
    //Socrate is a man
    Clause C3({Predicate(man_s,{socrate})});
    //Socrate is not mortal
    Clause C4({~Predicate(mortal_s,{aplaton})});
    System S({C1,C2,C3,C4},factory);
    std::cout << "Can Socrate be immortal?: ";
    std::cout << std::boolalpha <<S.check_consistency();
    return 0;
}
