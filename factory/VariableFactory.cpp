//
// Created by ramizouari on 13/04/2021.
//

#include "VariableFactory.h"
#include <queue>

void VariableFactory::resize(int s)
{
    int n=S_map.size();
    for(int i=n;i<s;i++)
    {
        Variable *w=new Variable;
        S_map[i]=w;
        id_map[w]=i;
    }
    for(int i=n-1;i>=s;i--)
    {
        id_map.erase(S_map[i]);
        delete S_map[i];
        S_map.erase(i);
    }
}

int VariableFactory::rename(Clause &C, int offset)
{

    resize(std::max<int>(S_map.size(),offset+C.count_variables()));
    std::unordered_map<int,Symbol*> f;
    std::unordered_map<Symbol*,int> g;
    std::queue<Literal*> Q;
    int k=0;
    for(auto &P:C.predicates)
    {
        for(auto &L:P.args) Q.push(&L);
        while(!Q.empty())
        {
            auto& w=*Q.front();
            if(w.is_variable())
            {
                if(g.contains(w.S))
                    w.S=f[g[w.S]];
                else
                {
                    auto p=S_map[offset];
                    f[offset]=p;
                    g[w.S]=offset;
                    offset++;
                    k++;
                    w.S=p;
                }

            }
            else for(auto &u:w.args) Q.push(&u);
            Q.pop();
        }
    }
    return k;
}

VariableFactory::VariableFactory() {
    counter++;
}

VariableFactory::~VariableFactory() {
    counter--;
    if(counter==0) resize(0);
}

Variable *VariableFactory::by_id(int id) const {
    return S_map[id];
}

Variable *VariableFactory::new_instance()
{
    Variable *w=new Variable;
    int n=S_map.size();
    S_map[n]=w;
    id_map[w]=n;
    return w;
}

VariableFactory::VariableFactory(VariableFactory &) {
    counter++;
}


VariableFactory::VariableFactory(VariableFactory &&) {
    counter++;
}