#define STRESS
#include "library/template.hpp"

std::mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

template<class IntType = long long> IntType uniform(IntType l, IntType r) {
    static_assert(std::is_integral<IntType>::value,
            "template argument must be an integral type");
    assert(l <= r);
    return std::uniform_int_distribution<IntType>{l, r}(rnd);
}
template<class RealType = double> RealType uniform_real(RealType l, RealType r) {
    static_assert(std::is_floating_point<RealType>::value,
                  "template argument must be an floating point type");
    assert(l <= r);
    return std::uniform_real_distribution<RealType>{l, r}(rnd);
}
template<class Iter> void shuffle(const Iter& first, const Iter& last) {
    std::shuffle(first, last, rnd);
}
template<class T> void shuffle(vector<T>& a){
    return shuffle(a.begin(), a.end());
}

template<typename T = long long> vector<T> RandomArray(int n){
    return RandomArray<T>(n, numeric_limits<T>::min() / T(2));
}
template<typename T = long long> vector<T> RandomArray(int n, T l,
        T r = numeric_limits<T>::max() / T(2)){
    vector<T> rand(n);
    for (int x = 0; x < n; ++x) rand[x] = uniform<T>(l, r);
    return rand;
}
template<typename T = long long> vector<T> RandomUniqueArray(int n, T l,
        T r = numeric_limits<T>::max() / T(2), bool SORTED = false){
    assert(r == numeric_limits<T>::max() / T(2) or n <= r - l + 1);
    set<T> rand;
    while ((int) rand.size() < n) rand.insert(uniform<T>(l, r));
    if (SORTED) return {rand.begin(), rand.end()};
    vector<T> res = {rand.begin(), rand.end()};
    shuffle(res);
    return res;
}
template<typename T = int> vector<T> RandomPermutation(int n, int start = 1) {
    vector<T> perm(n);
    iota(perm.begin(), perm.end(), start);
    shuffle(perm);
    return perm;
}

string RandomString(int n, char start = 'a', char end = 'z') {
    string str(n, '\0');
    for (int i = 0; i < n; i++) {
        str[i] = start + uniform<int>(0, end - start);
    }
    return str;
}
vector<string> RandomStrings(int n, int minlen, int maxlen, char a = 'a', char b = 'z') {
    vector<string> strs(n);
    for (int i = 0; i < n; i++) {
        strs[i] = RandomString(uniform<int>(minlen, maxlen), a, b);
    }
    return strs;
}

int main(){
    int a = uniform(1, 10);
    int b = uniform(1, 10);
    print(a, b);
    return 0;
}