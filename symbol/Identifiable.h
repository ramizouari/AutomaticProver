//
// Created by ramizouari on 17/04/2021.
//

#ifndef AUTOMATICPROVER_IDENTIFIABLE_H
#define AUTOMATICPROVER_IDENTIFIABLE_H

template<typename I>
class Identifiable {
public:
    virtual ~Identifiable(){}
    virtual I get_name() = 0;
};


#endif //AUTOMATICPROVER_IDENTIFIABLE_H
