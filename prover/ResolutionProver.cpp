//
// Created by ramizouari on 22/04/2021.
//

#include "exception/ProofLengthException.h"
#include "ResolutionProver.h"

void ResolutionProver::prove(const Clause &C1,const Clause &C2, std::queue<Clause> &Q) {
    for(int b=0;b<2;b++)
    {
        int p1=b?0:C1.count_affirmation(),q1=b?C1.count_affirmation():C1.count_predicates();
        int p2=!b?0:C2.count_affirmation(),q2=!b?C2.count_affirmation():C2.count_predicates();
        for (int i = p1; i < q1; i++)
            for (int j = p2; j < q2; j++)
            {
                Clause S1(C1), S2(C2);
                if (auto sigma = pgu(S1.get_args()[i], ~S2.get_args()[j]);sigma.has_value()) {
                    sigma.value()(S1);
                    sigma.value()(S2);
                    Clause R;
                    for (int s = 0; s < S1.count_predicates(); s++) {
                        if (s == i) continue;
                        R |= S1.get_args()[s];
                    }
                    for (int s = 0; s < S2.count_predicates(); s++)
                    {
                        if (s == j) continue;
                        R |= S2.get_args()[s];
                    }
                    if (R.is_empty())
                        consistent = false;
                    if (!T.contains(R)) {
                        bool is_true_statement = false;
                        for (int i = 0; i < R.count_affirmation(); i++)
                            for (int j = R.count_affirmation(); j < R.count_predicates(); j++)
                                if (unifiable(R.get_args()[i], ~R.get_args()[j]))
                                {
                                    is_true_statement = true;
                                    break;
                                }
                        if (!is_true_statement) {
                            clause_count += R.count_predicates();
                            Q.push(R);
                        }
                    }


                }
            }
    }
}

bool ResolutionProver::prove_inconsistency(const PredicateSystem &A)
{
    std::queue<Clause> Q;
    for(auto s:A.get_goals())
        Q.push(s);
    std::unordered_set<Clause>P;
    std::copy(A.get_hypotheseses().begin(),A.get_hypotheseses().end(),
              std::inserter(T,T.begin()));
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
    return !consistent;
}

std::vector<Clause> ResolutionProver::get_theorems() const {
    std::vector<Clause> _T;
    std::copy(T.begin(),T.end(),std::back_inserter(_T));
    return _T;
}

void ResolutionProver::set_limit(int L) {
    clause_count_limit=L;
}
