//
// Created by ramizouari on 15/04/2021.
//

#include "ProofLengthException.h"

const char* ProofLengthException::what() const noexcept {
    return "proof size is getting too big, aborting...";
}
