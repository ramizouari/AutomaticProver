//
// Created by ramizouari on 13/04/2021.
//

#ifndef AUTOMATICPROVER_SYMBOL_H
#define AUTOMATICPROVER_SYMBOL_H


class Symbol {
public:
    virtual ~Symbol(){};
    virtual bool is_variable()=0;

    virtual int arg_count() = 0;
    friend class SymbolFactory;
};


#endif //AUTOMATICPROVER_SYMBOL_H
