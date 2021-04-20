//
// Created by ramizouari on 19/04/2021.
//

#include "PrepositionalSystem.h"
#include "exception/ProofLengthException.h"

PrepositionalSystem::PrepositionalSystem(const std::vector<Clause> &_S) : System(_S) {

}

bool PrepositionalSystem::prove(Clause C1, Clause C2, std::queue<Clause> &Q) {
    bool proof=false;
    for(int i=0;i<C1.predicates.size();i++) for(int j=0;j<C2.predicates.size();j++)
        {
            Clause S1(C1),S2(C2);
            if (S1.predicates[i]==~S2.predicates[j])
            {
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
                        if(R.predicates[i]==~R.predicates[j])
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

bool PrepositionalSystem::check_consistency() {
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

std::vector<Clause> PrepositionalSystem::get_theorems() {
    check_consistency();
    std::vector<Clause> T_;
    std::copy(T.begin(),T.end(),std::back_inserter(T_));
    return T_;
}
