//
// Created by ramizouari on 22/04/2021.
//

#ifndef AUTOMATICPROVER_LINEARRESOLUTIONPROVER_H
#define AUTOMATICPROVER_LINEARRESOLUTIONPROVER_H
#include "ResolutionProver.h"

class LinearResolutionProver:public ResolutionProver {
public:
    void prove(const Clause &A,const Clause &B, std::queue<Clause> &Q) override;
};


#endif //AUTOMATICPROVER_LINEARRESOLUTIONPROVER_H
