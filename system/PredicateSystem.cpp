//
// Created by ramizouari on 14/04/2021.
//

#include "PredicateSystem.h"
#include "predicate/Predicate.h"
#include "exception/ProofLengthException.h"
#include <stack>
#include <queue>
#include <unordered_set>
#include "prover/Prover.h"

bool PredicateSystem::prove(Clause C1, Clause C2)
{
    bool proof=false;
    for(int i=0;i<C1.predicates.size();i++) for(int j=0;j<C2.predicates.size();j++)
        if(auto P=pgu(C1.predicates[i],~C2.predicates[j],C1,C2);P.has_value())
        {
            proof=true;
            Clause R;
            for(int s=0;s<C1.predicates.size();s++)
            {
                if(s==i) continue;
                R.predicates.push_back(C1.predicates[s]);
            }
            for(int s=0;s<C2.predicates.size();s++)
            {
                if(s==j) continue;
                R.predicates.push_back(C2.predicates[s]);
            }
            if(R.is_empty())
                consistent=false;
            clause_count+=R.count_predicates();
            T.insert(R);
        }
    return proof;
}

PredicateSystem::PredicateSystem(const std::vector<Clause> &_S,VariableFactory &_F):System(_S),F(_F)
{
    rename_all();
}

bool PredicateSystem::is_consistent() const {
    return consistent;
}

bool PredicateSystem::check_consistency() {
    std::queue<Clause> Q;
    for(auto s:S)
        Q.push(s);
    while(!Q.empty())
    {
        if(clause_count>clause_count_limit)
            throw ProofLengthException();
        auto C = Q.front();
        T.insert(C);
        bool any_proof=false;
        for(auto U:T)
            prove(C,U,Q);
        if(!consistent)
            break;
        Q.pop();
    }
    while(!Q.empty()) {
        T.insert(Q.front());
        Q.pop();
    }
    return consistent;
}

bool PredicateSystem::prove(Clause C1, Clause C2, std::queue<Clause> &Q) {
    bool proof=false;
    for(int i=0;i<C1.predicates.size();i++) for(int j=0;j<C2.predicates.size();j++)
    {
            Clause S1(C1),S2(C2);
            if (auto P = pgu(S1.predicates[i], ~S2.predicates[j], S1, S2);P.has_value()) {
                proof = true;
                Clause R;
                for (int s = 0; s < S1.predicates.size(); s++) {
                    if (s == i) continue;
                    R.predicates.push_back(S1.predicates[s]);
                }
                for (int s = 0; s < S2.predicates.size(); s++) {
                    if (s == j) continue;
                    R.predicates.push_back(S2.predicates[s]);
                }
                if (R.is_empty())
                    consistent = false;
                if (!T.contains(R))
                {
                    bool is_true_statement=false;
                    for(int i=0;i<R.predicates.size();i++) for(int j=i+1;j<R.predicates.size();j++)
                        if(unifiable(R.predicates[i],~R.predicates[j]))
                        {
                            is_true_statement=true;
                            break;
                        }
                    if(!is_true_statement)
                    {
                        clause_count+=R.count_predicates();
                        Q.push(R);
                    }
                }


            }
        }
    return proof;
}


void PredicateSystem::rename_all()
{
    int n=0;
    for(auto &C:S)
        n+=F.rename(C,n);

}

std::vector<Clause> PredicateSystem::get_theorems() {
    check_consistency();
    std::vector<Clause> T_;
    std::copy(T.begin(),T.end(),std::back_inserter(T_));
    return T_;
}

PredicateSystem PredicateSystem::operator&(PredicateSystem S)  const
{
    PredicateSystem A(*this);
    std::copy(S.S.begin(),S.S.end(),std::back_inserter(A.S));
    A.rename_all();
    return A;
}

PredicateSystem PredicateSystem::operator&(Clause S)  const
{
    PredicateSystem A(*this);
    A.add_clause(S);
    A.rename_all();
    return A;
}

PredicateSystem PredicateSystem::operator&(Predicate S)  const
{
    PredicateSystem A(*this);
    A.add_clause(S);
    A.rename_all();
    return A;
}

PredicateSystem::PredicateSystem(VariableFactory &_F) :F(_F){

}

void PredicateSystem::merge(PredicateSystem S1) {
    std::copy(S1.S.begin(),S1.S.end(),std::back_inserter(S));
    rename_all();
}

PredicateSystem &PredicateSystem::operator&=(PredicateSystem S) {
    merge(S);
    return *this;
}

PredicateSystem &PredicateSystem::operator&=(Clause C) {
    merge(C);
    return *this;
}

PredicateSystem &PredicateSystem::operator&=(Predicate C) {
    merge(C);
    return *this;
}

void PredicateSystem::merge(Clause C)
{
    add_clause(C);
    rename_all();
}

void PredicateSystem::merge(Predicate P)
{
    add_clause(Clause(P));
    rename_all();
}

void PredicateSystem::set_limit(int L) {
    clause_count_limit=L;
}

std::vector<SymbolicFunction*> PredicateSystem::get_functions() const {
    std::unordered_set<SymbolicFunction*> F;
    std::queue<Literal> Q;
    for(auto C:S) for(auto P:C.predicates) for(auto u:P.get_args())
            {
                Q.push(u);
                while(!Q.empty())
                {
                    auto w=Q.front();
                    if(!w.is_variable())
                        F.insert(dynamic_cast<SymbolicFunction*>(w.get()));
                    for(auto v:w.get_args())
                        Q.push(v);
                    Q.pop();
                }
            }
    std::vector<SymbolicFunction*> R;
    std::copy(F.begin(),F.end(),std::back_inserter(R));
    return R;
}

bool PredicateSystem::check_consistency(Prover &P) {
    return !P.prove_inconsistency(*this);
}
