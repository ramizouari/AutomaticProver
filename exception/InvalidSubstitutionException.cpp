//
// Created by ramizouari on 21/04/2021.
//

#include "InvalidSubstitutionException.h"

const char *InvalidSubstitutionException::what() const noexcept {
    return "Attempting to generate an invalid substitution";
}
