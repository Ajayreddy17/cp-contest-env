#include "library/template.hpp"
#include "library/poly/convolution.hpp"

using mint = modint998;

int main(){
    
    vector<mint> a = {1, 3, 4, 5};
    vector<mint> b = {3, 4, 5};
    print(convolution(a, b));;
    return 0;
}