//
// Created by ramizouari on 18/04/2021.
//

#ifndef AUTOMATICPROVER_SYSTEMWITHTOTALORDER_H
#define AUTOMATICPROVER_SYSTEMWITHTOTALORDER_H
#include "SystemWithPartialOrder.h"

class SystemWithTotalOrder:public SystemWithPartialOrder
{
public:
    SystemWithTotalOrder(IdentifiedVariableFactory<std::string> &_F,std::string order_name);

};


#endif //AUTOMATICPROVER_SYSTEMWITHTOTALORDER_H
