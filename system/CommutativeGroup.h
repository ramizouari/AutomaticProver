//
// Created by ramizouari on 20/04/2021.
//

#ifndef AUTOMATICPROVER_COMMUTATIVEGROUP_H
#define AUTOMATICPROVER_COMMUTATIVEGROUP_H
#include "Group.h"

class CommutativeGroup:public Group {
protected:
    CommutativeGroup(IdentifiedVariableFactory<std::string> &_F,std::string op_name,std::string e_name);
public:
    CommutativeGroup(IdentifiedVariableFactory<std::string> &_F);
};


#endif //AUTOMATICPROVER_COMMUTATIVEGROUP_H
