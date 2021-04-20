//
// Created by ramizouari on 20/04/2021.
//

#ifndef AUTOMATICPROVER_MEDIANALGEBRA_H
#define AUTOMATICPROVER_MEDIANALGEBRA_H
#include "../SystemWithEquality.h"

class MedianAlgebra :public SystemWithEquality
{
    IdentifiedSymbolicFunction_3<std::string> majority;
public:
    MedianAlgebra(IdentifiedVariableFactory<std::string> &_F);
    SymbolicFunction_3 & get_majority();
};


#endif //AUTOMATICPROVER_MEDIANALGEBRA_H
