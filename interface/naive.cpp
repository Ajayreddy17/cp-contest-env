#define STRESS
#include "library/template.hpp"

template<class T, class F>
void IterateAllPermutation(vector<T> p, const F fn){
    ranges::sort(p);
    do { fn(p); } while (next_permutation(p.begin(), p.end()));
}

template<class T, class F> // fn is score function, maximize fn
vector<T> IdealPermutation(vector<T> p, const F fn){
    ranges::sort(p);
    auto P = p;
    auto score = fn(p);
    do { if (chmax(score, fn(p))) P = p; } while (next_permutation(p.begin(), p.end()));
    return P;
}

template<class T, class F>
void IterateAllSubseq(vector<T>& p, const F fn){
    int n = (int) p.size();
    for (int mask = 0; mask < 1 << n; ++mask){
        vector<pair<T, int>> s;
        for (int x = 0; x < n; x++){
            if (mask & (1 << x)) s.emplace_back(p[x], x);
        }
        fn(s);
    }
}

int main(){

    Int(a, b);
    print(a + b);
    return 0;
}