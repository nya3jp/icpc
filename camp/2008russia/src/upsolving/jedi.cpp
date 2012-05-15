#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "jedi"



int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    int n, p;
    cin >> n >> p;

    int v[n][n];
    REP(i, n) REP(j, n)
        cin >> v[i][j];

    

    return 0;
}



