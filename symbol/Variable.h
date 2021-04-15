//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_VARIABLE_H
#define AUTOMATICPROVER_VARIABLE_H
#include "Symbol.h"

class Variable :public Symbol{
    int arg_count() override;
    bool is_variable() override;
};


#endif //AUTOMATICPROVER_VARIABLE_H
