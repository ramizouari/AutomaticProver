//
// Created by ramizouari on 14/04/2021.
//

#include "System.h"
#include "../predicate/Predicate.h"
#include "../exception/ProofLengthException.h"
#include <stack>
#include <queue>
#include <unordered_set>

bool System::prove(Clause C1, Clause C2)
{
    bool proof=false;
    for(int i=0;i<C1.predicates.size();i++) for(int j=0;j<C2.predicates.size();j++)
        if(Predicate P=pgu(C1.predicates[i],~C2.predicates[j],C1,C2);!P.is_empty())
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

System::System(const std::vector<Clause> &_S,VariableFactory F):S(_S)
{
    rename_all(F);
}

bool System::is_consistent() const {
    return consistent;
}

bool System::check_consistency() {
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
            return false;
        Q.pop();
    }
    return true;
}

bool System::prove(Clause C1, Clause C2, std::queue<Clause> &Q) {
    bool proof=false;
    for(int i=0;i<C1.predicates.size();i++) for(int j=0;j<C2.predicates.size();j++)
            if(Predicate P=pgu(C1.predicates[i],~C2.predicates[j],C1,C2);!P.is_empty())
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
                if(!T.contains(R))
                    Q.push(R);

            }
    return proof;
}

void System::add_clause(Clause C)
{
    S.push_back(C);
}

void System::rename_all(VariableFactory F)
{
    int n=0;
    for(auto &C:S)
        n+=F.rename(C,n);

}