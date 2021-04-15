cmake_minimum_required(VERSION 3.19)
project(AutomaticProver)

set(CMAKE_CXX_STANDARD 20)

add_executable(AutomaticProver main.cpp symbol/Symbol.h symbol/SymbolicFunction.cpp symbol/SymbolicFunction.h symbol/Variable.cpp symbol/Variable.h symbol/Literal.cpp symbol/Literal.h predicate/Clause.cpp predicate/Clause.h factory/VariableFactory.cpp factory/VariableFactory.h symbol/SymbolicPredicate.cpp symbol/SymbolicPredicate.h predicate/Predicate.cpp predicate/Predicate.h system/System.cpp system/System.h exception/ProofLengthException.cpp exception/ProofLengthException.h)