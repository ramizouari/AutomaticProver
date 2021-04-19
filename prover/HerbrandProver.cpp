//
// Created by ramizouari on 19/04/2021.
//

#include "HerbrandProver.h"
#include <algorithm>
#include <stack>

void HerbrandProver::prove_inconsistency(const System &A)
{
    auto C_set=A.get_hypotheseses();
    initialize(A);
    for(int i=0;i<n;i++)
    {
        //TODO: Prove for a single Herbrand iteration, then augment
        //..
        //System S(this->A,);
        augment();
    }

}

void HerbrandProver::initialize(const System &A)
{
    auto F_ptr=A.get_functions();
    std::list<SymbolicFunction*> F_list;
    std::vector<SymbolicFunction*> K;
    std::copy_if(F_ptr.begin(),F_ptr.end(),std::back_inserter(K),
                 [](auto a){return a->arg_count()==0;});
    std::transform(K.begin(),K.end(),std::back_inserter(K_set),[](auto u)
    {
        return dynamic_cast<SymbolicConstant*>(u);
    });
    std::sort(F_ptr.begin(),F_ptr.end(),[](auto a,auto b)
    {
        return a->arg_count()>b->arg_count();
    });
    while(!F_ptr.empty() && F_ptr.back()->arg_count()==0)
        F_ptr.pop_back();
    std::reverse(F_ptr.begin(),F_ptr.end());
    std::transform(F_ptr.begin(),F_ptr.end(),std::back_inserter(F_set),[](auto u)->SymbolicFunction&{return *u;});
    std::transform(K_set.begin(),K_set.end(),std::back_inserter(H),
                   [](auto u)->Literal
    {
        return u;
    });
    std::copy(C_set.begin(),C_set.end(),std::back_inserter(this->A));
}

void HerbrandProver::augment()
{
    using couple = std::pair<int,Literal>;
    std::vector<Literal> Q;
    std::vector<int> I;
    int p=H.size();
    for(auto f_ref:F_set)
    {
        auto& f=f_ref.get();
        auto m = f.arg_count();
        Q.resize(m,H[0]);
        I.resize(m,0);
        while(true)
        {
            I.back()++;
            int i;
            for(i =I.size()-1 ; i>0 && I[i]==p;i--)
            {
                I.back()=0;
                Q[i]=H[0];
                I[i-1]++;
            }
            if(I.front()==p)
                break;
            Q[i]=H[i];
            H.emplace_back(&f,Q);
        }
        Q[0]=H[0];
        I[0]=0;
    }
    std::list<Clause> C_list;
    std::copy(C_set.begin(),C_set.end(),std::inserter(C_list,C_list.begin()));
    while(!C_list.empty())
    {
        int r=C_list.size();
        for (auto C:C_list)
        {
            int s = C.count_variables();
            if(s==0)
            {
                A.push_back(C);
                continue;
            }
            Variable *S=C.find_first_variable();
            C_list.push_back(C);
            for(auto h:H)
            {
                Clause C_ = C;
                C_.rename(S,h);
                C_list.push_back(C_);
            }
        }
        while(r--) C_list.pop_front();
    }
}
