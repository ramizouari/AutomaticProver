//
// Created by ramizouari on 21/04/2021.
//

#ifndef AUTOMATICPROVER_INVALIDSUBSTITUTIONEXCEPTION_H
#define AUTOMATICPROVER_INVALIDSUBSTITUTIONEXCEPTION_H
#include <exception>

class InvalidSubstitutionException:public std::exception {
    const char* what() const noexcept override;

};


#endif //AUTOMATICPROVER_INVALIDSUBSTITUTIONEXCEPTION_H
