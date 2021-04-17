//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_VARIABLE_H
#define AUTOMATICPROVER_VARIABLE_H
#include "Symbol.h"
#include "IdentifiableSymbol.h"
#include <sstream>

class Variable :virtual  public IdentifiableSymbol<std::string>{

    int id;
    inline static int counter=0;
public:
    Variable();
    virtual int arg_count() override;
    virtual bool is_variable() override;
    virtual int variable_id() const;
    std::string get_name() override
    {
        std::stringstream s_stream;
        s_stream << id;
        std::string name;
        s_stream >> name;
        return "@"+name;
    }
};


#endif //AUTOMATICPROVER_VARIABLE_H
