#include<bits/stdc++.h>
using namespace std;

int main(int argc, int *argv[]){
    ifstream gen("in.txt");
    ifstream nai("naiveout.txt");
    ifstream sol("solout.txt");
    ofstream out("C:\\Users\\thati\\Cp\\cp-contest-env\\interface\\wrong.txt");
    string line;

    if (not argv[1]){
        out << "Test case: " << endl;
        while (getline(gen, line)) out << line << endl;
        out << "Naive output: " << endl;
        while (getline(nai, line)) out << line << endl;
        out << "Solution output: " << endl;
        while (getline(sol, line)) out << line << endl;
    }
    else{
        out << "Passed";
    }
    return 0;
}