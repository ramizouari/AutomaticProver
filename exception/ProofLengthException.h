//
// Created by ramizouari on 15/04/2021.
//

#ifndef AUTOMATICPROVER_PROOFLENGTHEXCEPTION_H
#define AUTOMATICPROVER_PROOFLENGTHEXCEPTION_H
#include <exception>

class ProofLengthException:public std::exception {
    const char* what() const noexcept override;
};


#endif //AUTOMATICPROVER_PROOFLENGTHEXCEPTION_H
