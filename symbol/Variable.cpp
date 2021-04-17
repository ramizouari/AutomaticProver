//
// Created by ramizouari on 13/04/2021.
//

#include "Variable.h"

int Variable::arg_count() {
    return 0;
}

bool Variable::is_variable() {
    return true;
}

Variable::Variable():id(counter) {
    counter++;
}

int Variable::variable_id() const {
    return id;
}
